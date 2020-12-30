#!/bin/bash
echo "###################################"
echo "####### Starting peers.. ##########"
echo "###################################"

# while status=$(docker inspect --format "{{.State.Status}}" bft.frontend.1000); [ $status != "running" ]; do
#   echo "Frontends are not ready"
#   sleep 1
# done

docker run --rm --network=HLF --name=0.peer.ibm.bft \
-e FABRIC_CFG_PATH=/bft-config/fabric/ \
--env CORE_VM_DOCKER_HOSTCONFIG_NETWORKMODE=HLF \
-v /home/anonymous/code/fabric-orderingservice/hlf_config/scripts/peer0_material:/bft-config/ \
-v /var/run/:/var/run/  \
hyperledger/fabric-peer:amd64-1.3.0 > logs/peer0.log 2>&1 &
