#!/bin/bash

configtxgen -profile BFTChannel -outputCreateChannelTx channel.tx -channelID mychannel
configtxgen -profile BFTChannel -outputAnchorPeersUpdate anchor.tx -channelID mychannel -asOrg IBM

peer channel create -o 1000.frontend.bft:7050 -c mychannel -f channel.tx
peer channel update -o 1000.frontend.bft:7050 -c mychannel -f anchor.tx
peer channel join -b mychannel.block

peer chaincode install -n example02 -v 1.3 -p github.com/hyperledger/fabric/examples/chaincode/go/example02/cmd

peer chaincode instantiate -o 1000.frontend.bft:7050 -C mychannel -n example02 -v 1.3 -c '{"Args":["init","a","100","b","200"]}'
