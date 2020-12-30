'use strict'


const Utils = require("./utils");
const fs = require("fs");

const log4js = require('log4js');
var logger = log4js.getLogger("network.js");
logger.level = "DEBUG";

class Network {
    constructor(config) {
        this.network = Utils.parseYaml(config);
        this.clientConfigs = {};
        // this._processConfiguration("workspaceRoot");
    }

    _processConfiguration(workspaceRoot) {
        logger.debug(workspaceRoot);
        // logger.debug(this.network)
        // const clients = this.getClients();
        // for (const client of clients) {
        //     this.clientConfigs[client] = this.network.clients[client];
        // }

    }
    getOrderer() {
        const orderers = this.network.orderers;
        for(const key in orderers){
            if(!orderers.hasOwnProperty(key)) {
                continue;
            }
            return key; // return the first orderer
        }
    }
    getInterval() {
        return parseInt(this.network.interval);
    }
    getTxns() {
        return parseInt(this.network.txns);
    }
    getAccounts() {
        return parseInt(this.network.accounts);
    }
    getUser() {
        return this.network.User;
    }
    getClientCryptoContent(client) {
        const clientObject = this.network.clients[client].client;


        const privateKey = clientObject.clientPrivateKey;
        const signedCert = clientObject.clientSignedCert;
        let privateKeyPEM;
        let signedCertPEM;

        privateKeyPEM = fs.readFileSync(privateKey.path);
        signedCertPEM = fs.readFileSync(signedCert.path);

        return {
            privateKeyPEM: privateKeyPEM,
            signedCertPEM: signedCertPEM
        };
    }
    getAdminCryptoContentOfOrganization(org) {
        const orgObject = this.network.organizations[org];

        const privateKey = orgObject.adminPrivateKey;
        const signedCert = orgObject.signedCert;

        let privateKeyPEM;
        let signedCertPEM;

        privateKeyPEM = fs.readFileSync(privateKey.path);
        signedCertPEM = fs.readFileSync(signedCert.path);

        // if either is missing, the result is undefined
        if (!privateKeyPEM || !signedCertPEM) {
            return undefined;
        }

        return {
            privateKeyPEM: privateKeyPEM,
            signedCertPEM: signedCertPEM
        };
    }

    getMspIdOfOrganization(org) {
        return this.network.organizations[org].mspid;
    }

    getOrganizations() {
        logger.debug("orgs");
        const result = new Set();
        const orgs = this.network.organizations;
        for(const key in orgs) {
            if(!orgs.hasOwnProperty(key)) {
                continue;
            }
            result.add(key.toString());
        }
        return result;
    }
    getPeersOfOrganization(org) {
        return new Set(this.network.organizations[org].peers);
    }
    getClientsOfOrganization(org) {
        const clients = this.getClients();
        const result = new Set();

        for (const client of clients) {
            if (this.network.clients[client].client.organization === org) {
                result.add(client);
            }
        }
        return result;
    }

    getOrganizationOfPeer(peer){
        const orgs = this.network.getOrganizations();
        for(const org of orgs){
            const peers = this.getPeersOfOrganization(org);
            if(peers.has(peer)) {
                return org;
            }
        }
        throw new Error(`peer:${peer} not found in any organizaitons`);
    }

    

    getClients() {
        const result = new Set();
        const clients = this.network.clients;
        for(const key in clients) {
            logger.info(key);
            if(!clients.hasOwnProperty(key)) {
                continue;
            }
            result.add(key.toString());
        }
        return result;
    }
    getChannelName() {
        const channels = this.network.channels;
        for(const key in channels) {
            if(!channels.hasOwnProperty(key)) {
                continue;
            }
            return key.toString();
        }
        throw new Error("no channel found");
    }
    getOrdererUrl() {
        return this.network.orderers[this.getOrderer()].url.toString();
    }
    getTargetPeers() {
        const result = new Set();
        const peers = this.network.target_Peers;
        for(const idx in peers) {
            const peerName = peers[idx];
            // logger.debug(peer);
            const peer = this.network.peers[peerName];
            result.add(peer);
        }
        return result;
    }

    getChannel() {
        const result = new Set();
        const channels = this.network.channels;
        for(const key in channels) {
            if(!channels.hasOwnProperty(key)) {
                continue;
            }
            return this.network.channels[key.toString()];
        }
        throw new Error("no channel found");
    }
    getChaincodeOfChannel(channel) {
        return this.network.channels[channel].chaincodes[0];
    }

    getNewNetworkObject() {
        return Utils.yaml2obj(Utils.obj2yaml(this.network));
    }

    getClientObj(client) {
        return this.network.clients[client].client;
    }

    getOrganizationOfClient(client) {
        return this.network.clients[client].client.organization;
    }

}

module.exports = Network;
