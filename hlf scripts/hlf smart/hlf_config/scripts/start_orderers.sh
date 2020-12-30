#!/bin/bash

echo "###################################"
echo "##### Starting orderers... ########"
echo "###################################"

rm -rf logs
mkdir logs

docker run --rm --network=temp_exp --name=0.node.bft \
-e NODE_CONFIG_DIR=/bft-config/config \
-v /home/anonymous/code/fabric-orderingservice/hlf_config/scripts/orderer0_material/:/bft-config/  \
bftsmart/fabric-orderingnode:amd64-1.3.0 0 > logs/orderer0.log 2>&1 &

docker run --rm --network=temp_exp --name=1.node.bft \
-e NODE_CONFIG_DIR=/bft-config/config \
-v /home/anonymous/code/fabric-orderingservice/hlf_config/scripts/orderer1_material/:/bft-config/  \
bftsmart/fabric-orderingnode:amd64-1.3.0 1 > logs/orderer1.log 2>&1 &

docker run --rm --network=temp_exp --name=2.node.bft \
-e NODE_CONFIG_DIR=/bft-config/config \
-v /home/anonymous/code/fabric-orderingservice/hlf_config/scripts/orderer2_material/:/bft-config/  \
bftsmart/fabric-orderingnode:amd64-1.3.0 2 > logs/orderer2.log 2>&1 & 

docker run --rm --network=temp_exp --name=3.node.bft \
-e NODE_CONFIG_DIR=/bft-config/config \
-v /home/anonymous/code/fabric-orderingservice/hlf_config/scripts/orderer3_material/:/bft-config/  \
bftsmart/fabric-orderingnode:amd64-1.3.0 3 > logs/orderer3.log 2>&1 &
