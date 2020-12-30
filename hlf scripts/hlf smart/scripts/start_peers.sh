#!/bin/bash
echo "###################################"
echo "Start peers..."
echo "###################################"

# while status=$(docker inspect --format "{{.State.Status}}" bft.frontend.1000); [ $status != "running" ]; do
#   echo "Frontends are not ready"
#   sleep 1
# done
sleep 10

echo "Frontends are ready"

docker run --rm --network=HLF -v /var/run/:/var/run/ --env GOPATH=/opt/gopath --env CORE_VM_DOCKER_HOSTCONFIG_NETWORKMODE=HLF --name=bft.peer.0 hyperledger/fabric-peer:amd64-1.3.0 > logs/peer0.log 2>&1 &
docker run --rm --network=HLF -v /var/run/:/var/run/ --env GOPATH=/opt/gopath --env CORE_VM_DOCKER_HOSTCONFIG_NETWORKMODE=HLF --name=bft.peer.1 hyperledger/fabric-peer:amd64-1.3.0 > logs/peer1.log 2>&1 &
