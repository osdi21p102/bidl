'use strict'

const Utils = require('./utils');
const Network = require('./network');
const log4js = require('log4js');
var logger = log4js.getLogger("test.js");
const WL = require('./workload');
logger.level = "DEBUG";



var check = Utils.parseYaml('./example.yaml')

logger.info(check.clients["User4"].client)
var org = new Set();
const orgs = check.organizations;
for(const key in orgs) {
    if(!orgs.hasOwnProperty(key)) {
        logger.debug(key.toString());
        continue;
    }
    org.add(key.toString());
}

logger.info(org);

logger.info(check.channels[0]);
logger.info(check.channels['mychannel'].chaincodes[0]);

var a = [1];

logger.info(a.length);


var net = new Network('network.yaml');
logger.info(net.getOrganizations());

logger.info(process.argv[2]);


function print(msg) {
    logger.info(msg);
}

logger.info(net.getTargetPeers());
logger.info(net.getOrdererUrl());
logger.info(net.getOrderer());
print(net.getUser());
print(net.getTxns());

WL.init(10);

// for(let i = 0; i < 20; i++) {
//     print(WL.generateWorkload().fcn);
// }


console.log(new Date().toISOString());
console.log(new Date().toISOString());
console.log(new Date());