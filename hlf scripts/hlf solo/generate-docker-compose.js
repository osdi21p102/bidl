'use strict'
const fs = require('fs');
const yaml = require('js-yaml');

function print(msg) {
    console.log(msg);
}

var template = fs.readFileSync("docker-compose-template.yaml");
var content = fs.readFileSync("client-config.yaml");
const obj = yaml.load(content);

var result = {};
result.version = '3';
result.networks = {};
result.networks.HLF = {};
result.networks.HLF.external = true;
result.services = {};

var templateObj = yaml.load(template)
result.services.orderer = templateObj.services["orderer"];

for(let i = 0; i < obj.Peers; i++) {
    result.services[`peer${i}`] = templateObj.services[`peer${i}`];
}

result.services["cli"] = templateObj.services["cli"];
result.services["cli"].depends_on = result.services["cli"].depends_on.slice(0, obj.Peers+1);


fs.writeFileSync("docker-compose.yaml", yaml.dump(result));

