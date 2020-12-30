#!/bin/bash

echo "###################################"
echo "Start orderers..."
echo "###################################"

docker run --rm --network=HLF --name=bft.node.0 bftsmart/fabric-orderingnode:amd64-1.3.0 0 > logs/orderer1.log 2>&1 &
docker run --rm --network=HLF --name=bft.node.1 bftsmart/fabric-orderingnode:amd64-1.3.0 1 > logs/orderer2.log 2>&1 &
docker run --rm --network=HLF --name=bft.node.2 bftsmart/fabric-orderingnode:amd64-1.3.0 2 > logs/orderer3.log 2>&1 &
docker run --rm --network=HLF --name=bft.node.3 bftsmart/fabric-orderingnode:amd64-1.3.0 3 > logs/orderer4.log 2>&1 &