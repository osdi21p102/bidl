#!/bin/bash
echo "###################################"
echo "Start clients..."
echo "###################################"

while status=$(docker inspect --format "{{.State.Status}}" bft.peer.1); [ $status != "running" ]; do
  echo "peers are not ready"
  sleep 1
done

echo "peers are ready"

docker run --rm --network=HLF --name=bft.cli.0 -e CORE_PEER_ADDRESS=bft.peer.0:7051 bftsmart/fabric-tools:amd64-1.3.0 > logs/cli0.log 2>&1 &
docker run --rm --network=HLF --name=bft.cli.1 -e CORE_PEER_ADDRESS=bft.peer.1:7051 bftsmart/fabric-tools:amd64-1.3.0 > logs/cli1.log 2>&1 &
