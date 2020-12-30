'use strict'

const FabricClient = require('fabric-client');
const Network = require('./network')
const Utils = require('./utils');
const log4js = require('log4js');
var logger = log4js.getLogger("client.js");
logger.level = "DEBUG";

class Client {

    constructor(networkConfigFile) {
        this.txCnt = 0;
        this.configVerify = false;
        this.configVerifyRW = true;
        this.network = new Network(networkConfigFile);
        this.fabadmins = new Map();
        this.fabclients = new Map();
    }

    async init() {
        await this._initializeAdmin();
        await this._initializeUsers();
        await this._installChaincode();
        await this._instantiateChaincode();
    }

    async _initializeAdmin() {
        logger.debug("run");
        const orgs = this.network.getOrganizations();
        for(const org of orgs) {
            logger.debug(`${org}`);
            console.log("jiang");
            const adminName = `admin.${org}`;
            const fabadmin = await this._prepareClientProfile(org, undefined);
            const admin = await this._getUserContext(fabadmin, adminName);
            if(admin) {
                this.fabadmins.set(org, fabadmin);
            } else {
                // throw new Error(`admin of ${org} is not initialized`);
                const cryptoContent = this.network.getAdminCryptoContentOfOrganization(org);
                await this._createUser(fabadmin, org, adminName, cryptoContent);
                this.fabadmins.set(org, fabadmin);
            }
        }
    }
    async _createUser(profile, org, userName, cryptoContent) {
        // set the user explicitly based on its crypto materials
        // createUser also sets the user context
        try {
            return await profile.createUser({
                username: userName,
                mspid: this.network.getMspIdOfOrganization(org),
                cryptoContent: cryptoContent
                // skipPersistence: true
            });
        } catch (err) {
            throw new Error(`Couldn't create ${profileName || ''} user object: ${err.message}`);
        }
    }


    async _initializeUsers() {
        const clients = this.network.getClients();
        for(const client of clients) {
            const org = this.network.getOrganizationOfClient(client);
            const fabclient = await this._prepareClientProfile(org, client);
            const user = await this._getUserContext(fabclient, client);
            if(user) {
                this.fabclients.set(client, fabclient);
            } else {
                const cryptoContent = this.network.getClientCryptoContent(client);
                await this._createUser(fabclient, org, client, cryptoContent);
                this.fabclients.set(org, fabclient);
                // throw new Error(`${client} of ${org} is not initialized`)
            }
        }
    }

    async _getUserContext(fabclient, clientName) {
        try {
            return await fabclient.getUserContext(clientName, true);
        }
        catch(err) {
            throw new Error(`getUserContext: ${(err.message || err)}`);
        }
    }


    async _prepareClientProfile(org, clientName) {
        let client = clientName;
        if(!client) {
            const clients = this.network.getClientsOfOrganization(org);
            if(clients.size < 1) {
                throw new Error(`not found admin client for ${org}`)
            }
            client = Array.from(clients)[0];
        }
        const fabclient = FabricClient.loadFromConfig(this.network.getNewNetworkObject());
        fabclient.loadFromConfig({
            version: '1.0',
            client: this.network.getClientObj(client)
        });
        try {
            await fabclient.initCredentialStores();
        }
        catch(err) {
            throw new Error(`initCreadentialStores: ${(err.message || err)}`);
        }
        return fabclient;
    }

    async installSmartContract(chaincode) {
        await this._installChaincode();
        await this._instantiateChaincode();
        await Utils.sleep(5000); // sleep 5s 
    }

    async _installChaincode() {
        const channel = this.network.getChannel();
        logger.info(`install chaincode for ${channel}`);
        const chaincode = channel.chaincodes[0]; // only support one chaincode for now
        const targetPeers = chaincode.targetPeers;
        if(targetPeers.size < 1) {
            logger.info(`no targetPeers to install`);
            return ;
        }
        const orgs = this.network.getOrganizations();
        for(const org of orgs) {
            const peersOfOrg = this.network.getPeersOfOrganization(org);
            const peersOfOrgTargets = targetPeers.filter(p => peersOfOrg.has(p));
            if(peersOfOrgTargets.size < 1) {
                continue;
            }
            const admin = this.fabadmins.get(org);
            const txId = admin.newTransactionID(true);
            logger.debug(`txid: ${txId._transaction_id}`)
            const request = {
                targets: peersOfOrgTargets,
                chaincodePath: chaincode.path,
                chaincodeId: chaincode.id,
                chaincodeVersion: chaincode.version,
                chaincodeType: chaincode.language,
                txId: txId
            };
            try{
                const propRespObj = await admin.installChaincode(request);
                const proposalResponses = propRespObj[0];
                Utils.assertDefined(proposalResponses);
                proposalResponses.forEach((propResponse, index) => {
                    if (propResponse instanceof Error) {
                        const errMsg = `Install proposal error for ${chaincode.id}@${chaincode.version} on ${peersOfOrgTargets[index]}: ${propResponse.message}`;
                        throw new Error(errMsg);
                    }
                    Utils.assertProperty(propResponse, 'propResponse', 'response');

                    /** @link{ResponseObject} */
                    Utils.assertProperty(response, 'response', 'status');
                    if(response.status !== 200) {
                        throw new Error(`install chaincode on ${org}${peersOfOrgTargets[index]} failed`);
                    }
                });
                logger.info(`install chaincode on ${org}@${peersOfOrgTargets} successfully`)
            }
            catch(err) {
                throw new Error(`install chaincode on ${org} failed`);
            }
        }
    }
    async _instantiateChaincode(){
        const channel = this.network.getChannel();
        logger.info(`instantiate chaincode for ${channel}`);
        const chaincode = channel.chaincodes[0]; // only support one chaincode for now
        const targetPeers = chaincode.targetPeers;
        if(targetPeers.size < 1) {
            logger.info(`no targetPeers to install`);
            return ;
        }
        const org = this.network.getOrganizations()[0];
        const admin = this.fabadmin.get(org);
        // TODO: check whether this chaincode is already instantiated, default false
        const txId = admin.newTransactionID(true);
        const request = {
            targets: targetPeers,
            chaincodeId: chaincode.id,
            chaincodeVersion: chaincode.version,
            chaincodeType: chaincode.language,
            args: [],
            fcn: 'init',
            'endorsement-policy': chaincode['endorsement-policy'],
            transientMap: {},
            txId: txId
        };
        let response;
        try {
            response = await admin.getChannel(channel, true).sendInstantiateProposal(request, 300000);
        }
        catch(err) {
            throw new Error("could not endorse instantiate proposal");
        }
        const proposalResponses = response[0];
        const proposal = response[1];
        proposalResponses.forEach((propResp, index) => {
            if(propResp.response.status !== 200) {
                throw new Error("Invalid endorsement for instantiate proposal");
            }
        });

        const eventSources = this._assembleTargetEventSource(channel, targetPeers);
        const eventPromises = [];
        try {
            // register event from peers
            eventSources.forEach((es) => {
                const promise = new Promise((resolve) => {
                    const timeoutHandle = setTimeout(() => {
                        es.eventHub.unregisterTxEvent(txId.getTransactionID(), false);
                        resolve(new Error(`Commit timeout for instantiating chaincode in ${channel} from ${es.prrt}`));

                    }, 300000);
                    es.eventHub.registerTxEvent(txId.getTransactionID(), 
                        (tx, code) => {
                            clearTimeout(timeoutHandle);
                            if(code !== 'VALID') {
                                resolve(new Error(`Invalid commit code for instantiating chaincode in ${channel} from ${es.peer}: ${code}`));
                            } else {
                                resolve(code);
                            }
                        }, 
                        (err) => {
                            clearTimeout(timeoutHandle);
                            resolve(`Event hub error from ${es.peer} during instantiating chaincode in ${channel}: ${err.message}`);
                        }
                    );
                    es.eventHub.connect();
                });
                eventPromises.push(promise);
            });

            // send tx for ordering
            const ordererRequest = {
                txId: txId, 
                proposalResponses: proposalResponses,
                proposal: proposal 
            };

            let broadcastResp;
            try {
                broadcastResp = await admin.getChannel(channel, true).sendTransaction(ordererRequest);
            } 
            catch(err) {
                throw new Error(`orderer error for instantiating chaincode: ${err.message}`);
            }
            if(broadcastResp.status !== 'SUCCESS') {
                throw new Error(`orderer error for instantiating chaincode: ${err.message}`);
            }

            const eventResults = await Promise.all(eventPromises);

            if(eventResults.some(er => er instanceof Error)) {
                throw new Error(`something wrong with event results, check(TODO)`);
            }

            logger.info(`successfully instantiate chaincode in ${channel}`);
        }
        finally {
            eventSources.forEach(es => {
                if(es.eventHub.isconnected()) {
                    es.eventHub.disconnect();
                }
            });
        }
        return true;
    }

    _assembleTargetEventSource(channel, targetPeers) {
        const eventSources = [];
        for(const peer of targetPeers) {
            const org = this.network.getOrganizationOfPeer(peer);
            const admin = this.fabadmins.get(org);
            const ehub = admin.getChannel(channel, true).newChannelEventHub(peer);
            eventSources.push({
                channel: [channel], 
                peer: peer, 
                eventHub: eventHub
            });

        }
        return eventSources;
    }
    async query(setting, timeout) {

    }

    async submitTransaction(setting, timeout) {
        const startTime = Date.now();
        this.txCnt++;
        //TODO: use User1, not admin(User0)
        const User = Array.from(this.network.getClients())[1]; 
        const invoker = this.fabclients.get(User);
        const txObj = invoker.newTransactionID();
        const txId = txObj.getTransactionID();

        logger.info(`start tx: ${txId}`);

        const targetPeers = [];
        const orgs = this.network.getOrganizations();
        for(const org of orgs) {
            const peers = this.network.getPeersOfOrganization(org);
            targetPeers.push(Array.from(peers)[this.txCnt % peers.size]);
            break;
        }
        if(targetPeers.length !== 1) {
            logger.fatal(`endorsement policy is wrong: len(targetPeers) = ${targetPeers.length}`);
            return false;
        }
        const proposalRequest = {
            chaincodeId: setting.chaincodeId,
            fcn: setting.chaincodeFunction,
            args: setting.chaincodeArguments || [],
            txId: txObj,
            transientMap: setting.transientMap,
            targets: targetPeers
        };
        try{
            const channel = invoker.getChannel(setting.channel, true);
            let proposalResponseObj = null;
            try {
                proposalResponseObj = await channel.sendTransactionProposal(proposalRequest, timeout);
            } 
            catch (err) {
                logger.fatal(`sendTransactionProposal${txId} failed`);
                return false;
            }
            const proposalResponses = proposalResponseObj[0];
            const proposal = proposalResponseObj[1];
            var errors = []
            proposalResponses.forEach((value, index) => {
                const targetName = targetPeers[index];
                if(value instanceof Error) {
                    logger.fatal(`proposalResponse error`);
                    errors.push(value);
                    return false;
                }
                const proposalResponse = value;
                if(this.configVerify) {
                    // verify signature
                    if(!channel.verifyProposalResponse(proposalResponse)) {
                        logger.fatal(`verify proposalResponse failed`);
                        errors.push(new Error(`verify failed`));
                        return false;
                    }
                    if(proposalResponse.response.status !== 200) {
                        logger.fatal(`endorsement faild(${proposalResponse.response.status}) on ${targetName}`);
                        errors.push(new Error(`endorsement faild(${proposalResponse.response.status}) on ${targetName}`));
                        return false;
                    }
                }
            });
            if(errors.length > 0) {
                //TODO: process errors
                return false;
            }

            if(this.configVerifyRW) { // read & write sets
                if(!channel.compareProposalResponseResults(proposalResponses)) {
                    logger.fatal(`read&write sets are not consistent`);
                    return false;
                }
            }

            // event
            const eventPromises = [];
            const eventSources = this._assembleTargetEventSource(channel, targetPeers);
            try {
                // register event from peers
                eventSources.forEach((es) => {
                    const promise = new Promise((resolve) => {
                        const timeoutHandle = setTimeout(() => {
                            es.eventHub.unregisterTxEvent(txId.getTransactionID(), false);
                            resolve(new Error(`Commit timeout for instantiating chaincode in ${channel} from ${es.prrt}`));

                        }, 300000);
                        es.eventHub.registerTxEvent(txId.getTransactionID(), 
                            (tx, code) => {
                                clearTimeout(timeoutHandle);
                                if(code !== 'VALID') {
                                    resolve(new Error(`Invalid commit code for instantiating chaincode in ${channel} from ${es.peer}: ${code}`));
                                } else {
                                    resolve(code);
                                }
                            }, 
                            (err) => {
                                clearTimeout(timeoutHandle);
                                resolve(`Event hub error from ${es.peer} during instantiating chaincode in ${channel}: ${err.message}`);
                            }
                        );
                        es.eventHub.connect();
                    });
                    eventPromises.push(promise);
                });

                // send tx for ordering
                const targetOrderer = this.network.getOrderer();
                try{
                    const orderer = channel.getOrderer(orderer);
                }
                catch (err) {
                    logger.fatal(`failed when getOrderer:${orderer}`);
                    return false;
                }

                const transactionRequest = {
                    proposalResponses: proposalResponses,
                    proposal: proposal,
                    orderer
                };

                let broadcastResponse = null;
                try {
                    // wrap it in a Promise to add explicit timeout to the call
                    const responsePromise = new Promise(async (resolve, reject) => {
                        const timeoutHandle = setTimeout(() => {
                            reject(new Error('TIMEOUT'));
                        }, this._getRemainingTimeout(startTime, timeout));
                    
                        const result = await channel.sendTransaction(transactionRequest);
                        clearTimeout(timeoutHandle);
                        resolve(result);
                    });
                    
                    broadcastResponse = await responsePromise;
                }
                catch(err) {
                    logger.fatal(`failed when sendTransaction(${txId})`);
                    return false;
                }
                if(broadcastResponse.status !== 200) {
                    logger.fatal(`sendTransaction response error: ${broadcastResponse.status}`);
                }

                // process events
                const eventResults = await Promise.add(eventPromises);
                const failedNotifications = eventResults.filter(er => !er.successful);
                if(failedNotifications.length > 0) {
                    //failed
                    logger.error(`${failedNotifications.length} peers set tx(${txId}) invalid`);
                    return false;
                } else {
                    //successful
                    //TODO: calculate latency
                }
            }
            finally {
                eventSources.forEach(es => {
                    if(es.eventHub.isconnected()) {
                        es.eventHub.disconnect();
                    }
                });
            }
        }
        catch(err) {
            logger.fatal(`unknown error: ${err.message}`);
            return false;
        }
        return true;
    }

    _getRemainingTimeout(start, original) {
        let newTimeout = original - (Date.now() - start);
        if (newTimeout < 1000) {
            logger.warn(`Timeout is too small, default value of 1000 ms is used instead`);
            newTimeout = 1000;
        }
        return newTimeout;
    }

    run() {
        workload = this._generateWorkload();
        var success = 0;
        var fail = 0;
        for(const tx of workload) {
            try{
                let res = this.submitTransaction(tx, 6000);
                if(!res) {
                    fail++;
                } else {
                    success++;
                }
            }
            catch (err) {
                fail++;
            }
        }
    }
}

module.exports = Client;