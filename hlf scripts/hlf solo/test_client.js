'use strict'

const FabricClient = require('fabric-client');
const log4js = require('log4js');


var logger = log4js.getLogger();
logger.level = "DEBUG";

var client = new FabricClient();

var channel = client.newChannel('mychannel');

var peer = client.newPeer("grpc://localhost:7051");
channel.addPeer(peer);
logger.debug(peer);

var orderer = client.newOrderer("grpc://localhost:7050");
channel.addOrderer(orderer);

logger.debug(client);



var test = FabricClient.loadFromConfig("example.yaml");
// logger.debug(test);
