'use strict';

let no_accounts = 0;
let account_array = [];
let accounts = 5000;
const initial_balance = 1000000;
const operation_type = ['transact_savings','deposit_checking','send_payment','write_check', 'amalgamate'];
let prefix;

const log4js = require('log4js');
var logger = log4js.getLogger("workload.js");
logger.level = "DEBUG";

/**
 * Get account index
 * @return {Number} index
 */
function getAccount() {
    return Math.floor(Math.random()*Math.floor(account_array.length));
}

/**
 * Get two accounts
 * @return {Array} index of two accounts
 */
function get2Accounts() {
    let idx1 = getAccount();
    let idx2 = getAccount();
    if(idx2 === idx1) {
        idx2 = getAccount();  // jyp: while???
    }
    return [idx1, idx2];
}

/**
 * Generate unique account key for the transaction
 * @returns {Number} account key
 **/
function generateAccount() {
    // should be [a-z]{1,9}
    if(typeof prefix === 'undefined') {
        prefix = process.pid;
    }
    let count = account_array.length+1;
    let num = prefix.toString() + count.toString();
    return parseInt(num);
}

/**
 * Generates random string.
 * @returns {string} random string from possible characters
 **/
function random_string() {
    let text = '';
    const possible = 'ABCDEFGHIJKL MNOPQRSTUVWXYZ abcdefghij klmnopqrstuvwxyz';

    for (let i = 0; i < 12; i++) {
        text += possible.charAt(Math.floor(Math.random() * possible.length));
    }
    return text;
}

/**
 * Generates small bank workload with specified number of accounts
 * and operations.
 * @returns {Object} array of json objects and each denotes
 * one operations
 **/
function generateWorkload() {
    let workload = [];
    if(no_accounts < accounts) {
        let acc_id = generateAccount();
        account_array.push(acc_id);
        let acc = {
            fcn: 'create_account',
            args: [acc_id, random_string(), initial_balance, initial_balance]
        }
        no_accounts++;
        return acc;
    }
    let op_index =  Math.floor(Math.random() * Math.floor(operation_type.length));
    let acc_index = getAccount();
    let random_op = operation_type[op_index];
    let random_acc = account_array[acc_index];
    let amount = Math.floor(Math.random() * 200);
    let op_payload;
    switch(random_op) {
    case 'transact_savings': {
        op_payload = {
            fcn: random_op,
            args: [amount, random_acc]
        };
        break;
    }
    case 'deposit_checking': {
        op_payload = {
            fcn: random_op,
            args: [amount, random_acc]
        };
        break;
    }
    case 'send_payment': {
        let accounts = get2Accounts();
        op_payload = {
            fcn: random_op,
            args: [amount, account_array[accounts[0]], account_array[accounts[1]]]
        };
        break;
    }
    case 'write_check': {
        op_payload = {
            fcn: random_op,
            args: [amount, random_acc]
        };
        break;
    }
    case 'amalgamate': {
        let accounts = get2Accounts();
        op_payload = {
            fcn: random_op,
            args: [account_array[accounts[0]], account_array[accounts[1]]]
        };
        break;
    }
    default: {
        throw new Error('Invalid operation!!!');
    }
    }
    return op_payload;
}

module.exports.init = function(init_accounts) {
    accounts = init_accounts;
}
module.exports.generateWorkload = generateWorkload;