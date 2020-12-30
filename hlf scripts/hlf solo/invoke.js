'use strict';
/*
* Copyright IBM Corp All Rights Reserved
*
* SPDX-License-Identifier: Apache-2.0
*/
/*
 * Chaincode Invoke
 */

var Fabric_Client = require('fabric-client');
var path = require('path');
var util = require('util');
var Utils = require('./utils');
var os = require('os');
const Network = require('./network');
const log4js = require('log4js');
var workload = require('./workload');

var logger = log4js.getLogger("invoke.js");
logger.level = "DEBUG";

var fabric_client = new Fabric_Client();
var member_user = null;
var channel = null;
var g_peer = null;
var store_path = path.join(__dirname, 'hfc-key-store');
console.log('Store path:'+store_path);
var network = new Network('./network.yaml');
workload.init(network.getAccounts());

function initNetwork() {
	try{
		// setup the fabric network
		channel = fabric_client.newChannel(network.getChannelName());
		const target_peers = network.getTargetPeers();
		for(const peer of target_peers) {
			var fabpeer = fabric_client.newPeer(peer.url);
			g_peer = fabpeer;
			channel.addPeer(fabpeer);
		}
		var order = fabric_client.newOrderer(network.getOrdererUrl());
		channel.addOrderer(order);
	} catch(err){
		throw new Error(`err: ${(err.message || err)}`);
	}
}

async function initUser() {
		// create the key value store as defined in the fabric-client/config/default.json 'key-value-store' setting
		return Fabric_Client.newDefaultKeyValueStore({ path: store_path
		}).then((state_store) => {
			// assign the store to the fabric client
			fabric_client.setStateStore(state_store);
			var crypto_suite = Fabric_Client.newCryptoSuite();
			// use the same location for the state store (where the users' certificate are kept)
			// and the crypto store (where the users' keys are kept)
			var crypto_store = Fabric_Client.newCryptoKeyStore({path: store_path});
			crypto_suite.setCryptoKeyStore(crypto_store);
			fabric_client.setCryptoSuite(crypto_suite);

			// get the enrolled user from persistence, this user will sign all requests
			return fabric_client.getUserContext(network.getUser(), true);
		}).then((user_from_store) => {
		    const user = network.getUser();
			if (user_from_store && user_from_store.isEnrolled()) {
				console.log(`Successfully loaded ${user} from persistence`);
				member_user = user_from_store;
			} else {
				throw new Error(`Failed to get ${user} .... run enrollUser.js`);
			}
		}).catch((err) => {
			throw new Error(`user error: ${(err.message || err)}`);
		});
}

function invoke(setting) {
	var st = Date.now();
	var timestamp = st;
	var tx_id = null;
	tx_id = fabric_client.newTransactionID();
	console.log("Assigning transaction_id: ", tx_id.getTransactionID());

	var request = {
		//targets: let default to the peer assigned to the client
		chaincodeId: "smallbank",
		fcn: setting.fcn,
		args: setting.args.map(String),
		chainId: "mychannel",
		txId: tx_id
	};

	// send the transaction proposal to the peers
	channel.sendTransactionProposal(request).then((results) => {
		var ed = Date.now();
		logger.info(`${tx_id.getTransactionID()} breakdown (0 sendTransactionProposal) at ${new Date()} (${ed-timestamp}ms)`);
		timestamp = ed;
		var proposalResponses = results[0];
		var proposal = results[1];
		let isProposalGood = false;
		if (proposalResponses && proposalResponses[0].response &&
			proposalResponses[0].response.status === 200) {
				isProposalGood = true;
				console.log('Transaction proposal was good');
			} else {
				console.error('Transaction proposal was bad');
			}
		if (isProposalGood) {
			console.log(util.format(
				'Successfully sent Proposal and received ProposalResponse: Status - %s, message - "%s"',
				proposalResponses[0].response.status, proposalResponses[0].response.message));

			// build up the request for the orderer to have the transaction committed
			var request = {
				proposalResponses: proposalResponses,
				proposal: proposal
			};

			// set the transaction listener and set a timeout of 30 sec
			// if the transaction did not get committed within the timeout period,
			// report a TIMEOUT status
			var transaction_id_string = tx_id.getTransactionID(); //Get the transaction ID string to be used by the event processing
			var promises = [];

			var sendPromise = channel.sendTransaction(request);
			promises.push(sendPromise); //we want the send transaction first, so that we know where to check status

			// // get an eventhub once the fabric client has a user assigned. The user
			// // is required bacause the event registration must be signed
			// // TODO: jyp: add more event_hubs
			// let event_hub = channel.newChannelEventHub(g_peer);

			// // using resolve the promise so that result status may be processed
			// // under the then clause rather than having the catch clause process
			// // the status
			// let txPromise = new Promise((resolve, reject) => {
			// 	let handle = setTimeout(() => {
			// 		event_hub.unregisterTxEvent(transaction_id_string);
			// 		event_hub.disconnect();
			// 		resolve({event_status : 'TIMEOUT'}); //we could use reject(new Error('Trnasaction did not complete within 30 seconds'));
			//  	}, 30000);
			// 	event_hub.registerTxEvent(transaction_id_string, (tx, code) => {
			// 		// this is the callback for transaction event status
			// 		// first some clean up of event listener
			// 		clearTimeout(handle);

			// 		// now let the application know what happened
			// 		var return_status = {event_status : code, tx_id : transaction_id_string};
			// 		if (code !== 'VALID') {
			// 			console.error('The transaction was invalid, code = ' + code);
			// 			resolve(return_status); // we could use reject(new Error('Problem with the tranaction, event status ::'+code));
			// 		} else {
			// 			console.log('The transaction has been committed on peer ' + event_hub.getPeerAddr());
			// 			resolve(return_status);
			// 		}
			// 	}, (err) => {
			// 		//this is the callback if something goes wrong with the event registration or processing
			// 		reject(new Error('There was a problem with the eventhub ::'+err));
			// 	},
			// 		{disconnect: true} //disconnect when complete
			// 	);
			// 	event_hub.connect();

			// });
			// promises.push(txPromise);

			return Promise.all(promises);
		 } else {
			console.error('Failed to send Proposal or receive valid response. Response null or status is not 200. exiting...');
			throw new Error('Failed to send Proposal or receive valid response. Response null or status is not 200. exiting...');
		}
	}).then((results) => {
		var ed = Date.now();
		logger.info(`${tx_id.getTransactionID()} breakdown (1 ordering & writeback) at ${new Date()} (${ed-timestamp}ms))`);
		logger.info(`${tx_id.getTransactionID()} breakdown (2 all) at ${new Date()} (${ed-st}ms)`);
		timestamp = ed;
		console.log('Send transaction promise and event listener promise have completed');
		// check the results in the order the promises were added to the promise all list
		if (results && results[0] && results[0].status === 'SUCCESS') {
			console.log('Successfully sent transaction to the orderer.');
		} else {
			console.error('Failed to order the transaction. Error code: ' + results[0].status);
		}

		// if(results && results[1] && results[1].event_status === 'VALID') {
		// 	console.log('Successfully committed the change to the ledger by the peer');
		// } else {
		// 	console.log('Transaction failed to be committed to the ledger due to ::'+results[1].event_status);
		// }
	}).catch((err) => {
		console.error('Failed to invoke successfully :: ' + err);
	});
}

async function run() {
	initNetwork();
	await initUser();
	var txns = network.getTxns();
	var i = 0;
	while(txns < 0 || i < txns) {
		i++;
		const setting = workload.generateWorkload();
		logger.info(setting);
		invoke(setting);
		await Utils.sleep(network.getInterval());
	}
}

run().then(()=>{
	logger.debug("success");
});
