#!/bin/bash

echo
echo " ____    _____      _      ____    _____ "
echo "/ ___|  |_   _|    / \    |  _ \  |_   _|"
echo "\___ \    | |     / _ \   | |_) |   | |  "
echo " ___) |   | |    / ___ \  |  _ <    | |  "
echo "|____/    |_|   /_/   \_\ |_| \_\   |_|  "
echo
echo "Build your first network (BYFN) end-to-end test"
echo
peer channel create -o frontend1000:7050 -c mychannel -f channel-artifacts/channel.tx
peer channel update -o frontend1000:7050 -c mychannel -f channel-artifacts/anchor.tx
# #
# #
CORE_PEER_ADDRESS=peer0:7051
CORE_PEER_MSPCONFIGPATH=/opt/gopath/src/github.com/hyperledger/fabric/peer/crypto/peerOrganizations/ibm.bft/users/Admin@ibm.bft/msp
peer channel join -b mychannel.block
 # 
peer chaincode install -n smallbank -v 1.3 -p github.com/chaincode/smallbank/go 
# # 
CORE_PEER_ADDRESS=peer1:7051 
peer channel join -b mychannel.block 
# # 
peer chaincode install -n smallbank -v 1.3 -p github.com/chaincode/smallbank/go 
CORE_PEER_ADDRESS=peer2:7051 
peer channel join -b mychannel.block 
# # 
peer chaincode install -n smallbank -v 1.3 -p github.com/chaincode/smallbank/go 
CORE_PEER_ADDRESS=peer3:7051 
peer channel join -b mychannel.block 
# # 
peer chaincode install -n smallbank -v 1.3 -p github.com/chaincode/smallbank/go 
# 
# 
CORE_PEER_ADDRESS=peer0:7051 
# # 
# # #
peer chaincode instantiate -o frontend1000:7050 -C mychannel -n smallbank -v 1.3 -c '{"Args":["init","a","100","b","200"]}' 
sleep 5
peer chaincode invoke -o frontend1000:7050 -C mychannel -n smallbank --peerAddresses peer0:7051 -c '{"Args":["create_account", "0916","a", "100","100"]}'  
#CORE_PEER_ADDRESS=3.peer.ibm.bft:7051 
sleep 5
peer chaincode query -C mychannel -n smallbank -c '{"Args":["query", "0916"]}'
