'use strict'
const fs = require('fs');
const yaml = require('js-yaml');

class Utils {
    static parseYaml(filepath) {
        return yaml.safeLoad(fs.readFileSync(filepath), 'utf8');
    }
    static obj2yaml(obj) {
        if(!obj) {
            throw new Error("obj is null or undefined");
        }
        try {
            return yaml.safeDump(obj);
        } 
        catch(err){
            throw new Error(`safeDump obj failed: ${(err.message || err)}`);
        }
    }
    static yaml2obj(str) {
        if(!str) {
            throw new Error('str is null or undefined');
        }
        try {
            return yaml.safeLoad(str);
        }
        catch(err) {
            throw new Error(`safeLoad failed: ${(err.message || err)}`);
        }
    }
    static assertProperty(object, objectName, propertyName) {
        if (!object.hasOwnProperty(propertyName) || object[propertyName] === undefined ||
            object[propertyName] === null) {
            throw new Error(`Property '${propertyName}' of ${objectName || 'object'} is missing, undefined or null`);
        }
    }
    static assertDefined(object, msg) {
        if (object === 'undefined' || object === null) {
            throw new Error(msg || 'Object is undefined or null!');
        }
    }
    static sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}


module.exports = Utils;