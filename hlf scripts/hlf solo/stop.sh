#!/bin/bash

work_path=$(dirname $(readlink -f $0))
echo "work_path is $work_path"

docker stack rm fabric
#docker stack rm sender
echo y | docker volume prune
