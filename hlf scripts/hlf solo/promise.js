'use strict'

function test(resolve, reject) {
    var timeout = Math.random();
    setTimeout(function() {
        if(timeout < 0.5) {
            resolve(timeout);
        } else {
            reject(timeout);
        }
    }, timeout*1000);
}

console.log("start");

var promises = [];

promises.push(new Promise(test)
    .then(function (result) {
        console.log("resolve1:", result);

    })
    .catch(function (result) {
        console.log("reject1:", result);

    })
    .finally(function () {
        console.log("finally1");
    }));

promises.push(new Promise(test)
    .then(function (result) {
        console.log("resolve2:", result);

    })
    .catch(function (result) {
        console.log("reject2:", result);

    })
    .finally(function () {
        console.log("finally2");
    }));

console.log("running");

Promise.all(promises);
console.log("end");

var s = '{"Args":["send_payment", "10", "T9c1QUeAaMLii5GTgZR8phDqQ2FhUgkg9LFCD9CR9Kqvqwn2gjjbPTHoR4GzSJ70", "el6fe66OoUN1GNdbweczHdLb1lcOi08HzaMzMFqjkO1oEi6FbDUN8PzLnC9VDGSx"]}';

var obj = JSON.parse(s);
console.log(obj);
