#!/bin/bash

work_path=$(dirname $(readlink -f $0))
echo "work_path is $work_path"

docker stack deploy --compose-file docker-compose.yaml fabric

sleep 5

#name=$(docker ps --filter ancestor=10.22.1.1:5000/fabric-tools:using_leveldb --format '{{.Names}}')
name=$(docker ps | grep async_inmemorydb | awk '{print $1}')
#name=$(docker ps | grep disable_vscc | awk '{print $1}')
#name=$(docker ps --filter ancestor=10.22.1.1:5000/fabric-tools:disable_vscc_db --format '{{.Names}}')
echo $name

docker exec -it $name bash scripts/script.sh
sleep 3

#docker stack deploy --compose-file sender.yaml sender
