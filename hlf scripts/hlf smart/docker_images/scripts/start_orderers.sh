#!/bin/bash

echo "###################################"
echo "Start orderers..."
echo "###################################"

docker run --rm --network=HLF --name=0.node.bft -e NODE_CONFIG_DIR=/bft-config/config/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/orderingnode_material/:/bft-config/ bftsmart/fabric-orderingnode:amd64-1.3.0 0 > logs/orderer0.log 2>&1 &
docker run --rm --network=HLF --name=1.node.bft -e NODE_CONFIG_DIR=/bft-config/config/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/orderingnode_material/:/bft-config/ bftsmart/fabric-orderingnode:amd64-1.3.0 1 > logs/orderer1.log 2>&1 &
docker run --rm --network=HLF --name=2.node.bft -e NODE_CONFIG_DIR=/bft-config/config/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/orderingnode_material/:/bft-config/ bftsmart/fabric-orderingnode:amd64-1.3.0 2 > logs/orderer2.log 2>&1 &
docker run --rm --network=HLF --name=3.node.bft -e NODE_CONFIG_DIR=/bft-config/config/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/orderingnode_material/:/bft-config/ bftsmart/fabric-orderingnode:amd64-1.3.0 3 > logs/orderer3.log 2>&1 &