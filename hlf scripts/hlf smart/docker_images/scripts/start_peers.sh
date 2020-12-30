#!/bin/bash
echo "###################################"
echo "Start peers..."
echo "###################################"

# while status=$(docker inspect --format "{{.State.Status}}" bft.frontend.1000); [ $status != "running" ]; do
#   echo "Frontends are not ready"
#   sleep 1
# done
# sleep 10

echo "Frontends are ready"

docker run --rm --network=HLF --name=0.peer.ibm.bft -e FABRIC_CFG_PATH=/bft-config/fabric/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/peer_material/:/bft-config/ -v /var/run/:/var/run/  hyperledger/fabric-peer:amd64-1.3.0 > logs/peer0.log 2>&1 &
# docker run --rm --network=HLF --name=1.peer.ibm.bft -e FABRIC_CFG_PATH=/bft-config/fabric/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/peer_material/:/bft-config/ -v /var/run/:/var/run/  hyperledger/fabric-peer:amd64-1.3.0 > logs/peer0.log 2>&1 &

