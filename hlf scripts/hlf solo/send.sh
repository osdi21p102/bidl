#!/bin/bash

#name=$(docker ps | grep inmemorydb | awk '{print $1}')
#name=$(docker ps | grep disable_vscc | grep tools | awk '{print $1}')
name=$(docker ps | grep async_inmemorydb | grep tools | awk '{print $1}')
echo $name

docker exec -it $name bash scripts/send.sh
