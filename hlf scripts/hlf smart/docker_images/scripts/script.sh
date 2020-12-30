#!/bin/bash

configtxgen -profile SampleSingleMSPChannel -outputCreateChannelTx channel.tx -channelID channel47
configtxgen -profile SampleSingleMSPChannel -outputAnchorPeersUpdate anchor.tx -channelID channel47 -asOrg SampleOrg
peer channel create -o bft.frontend.1000:7050 -c channel47 -f channel.tx 
peer channel update -o bft.frontend.1000:7050 -c channel47 -f anchor.tx
peer channel join -b channel47.block

