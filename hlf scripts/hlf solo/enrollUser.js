'use strict';
/*
* Copyright IBM Corp All Rights Reserved
*
* SPDX-License-Identifier: Apache-2.0
*/
/*
 * Enroll the admin user
 */

var Fabric_Client = require('fabric-client');

var path = require('path');
var util = require('util');
var os = require('os');
const Network = require('./network');
const log4js = require('log4js');
var logger = log4js.getLogger("client.js");
logger.level = "DEBUG";

const User = process.argv[2];
var network = new Network("network.yaml");

//
var fabric_client = new Fabric_Client();
var admin_user = null;
var store_path = path.join(__dirname, 'hfc-key-store');
console.log(' Store path:'+store_path);

// create the key value store as defined in the fabric-client/config/default.json 'key-value-store' setting
Fabric_Client.newDefaultKeyValueStore({ path: store_path
}).then((state_store) => {
    // assign the store to the fabric client
    fabric_client.setStateStore(state_store);
    var crypto_suite = Fabric_Client.newCryptoSuite();
    // use the same location for the state store (where the users' certificate are kept)
    // and the crypto store (where the users' keys are kept)
    var crypto_store = Fabric_Client.newCryptoKeyStore({path: store_path});
    crypto_suite.setCryptoKeyStore(crypto_store);
    fabric_client.setCryptoSuite(crypto_suite);
    var	tlsOptions = {
    	trustedRoots: [],
    	verify: false
    };
    // first check to see if the admin is already enrolled
    return fabric_client.getUserContext(User, true);
}).then((user_from_store) => {
    if (user_from_store && user_from_store.isEnrolled()) {
        console.log('Successfully loaded admin from persistence');
        admin_user = user_from_store;
        return null;
    } else {
        const org = network.getOrganizationOfClient(User);
        const mspid = network.getMspIdOfOrganization(org);
        var content = network.getClientCryptoContent(User);

        return fabric_client.createUser(
            {username: User,
                mspid: mspid,
                cryptoContent: content
            }
        ).then((user) => {
            admin_user = user;
            logger.debug(`enroll ${User} successfully`);
            return fabric_client.setUserContext(admin_user);
        }).catch((err) => {
            logger.debug(`${(err.message || err)}`);

        });
    }
}).then(() => {
    console.log('Assigned the user to the fabric client ::' + admin_user.toString());
}).catch((err) => {
    console.error('Failed to enroll User: ' + err);
});
