'use strict'

var bc = require('./workload')
const log4js = require('log4js');
var logger = log4js.getLogger("run.js");
logger.level = "DEBUG";

var promise = new Promise(bc.init)
    .then(bc.run)
    .then(function(result) {
        if(result) {
            logger.info("yes");
        } else {
            logger.info("no");
        }
    })
    .catch(function(reason) {
        logger.info(reason);
    });