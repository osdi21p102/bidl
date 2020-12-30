#!/bin/bash

docker tag bftsmart/fabric-orderingnode:amd64-1.3.0 10.22.1.1:5000/fabric-orderingnode:anonymous-dev 
docker tag bftsmart/fabric-frontend:amd64-1.3.0  10.22.1.1:5000/fabric-frontend:anonymous-dev 
docker tag hyperledger/fabric-tools:latest 10.22.1.1:5000/fabric-tools:anonymous-dev
docker tag hyperledger/fabric-peer:latest 10.22.1.1:5000/fabric-peer:anonymous-dev

docker push 10.22.1.1:5000/fabric-orderingnode:anonymous-dev
docker push 10.22.1.1:5000/fabric-frontend:anonymous-dev
docker push 10.22.1.1:5000/fabric-peer:anonymous-dev
docker push 10.22.1.1:5000/fabric-tools:anonymous-dev


ssh anonymous@10.22.1.1 "docker pull 10.22.1.1:5000/fabric-orderingnode:anonymous-dev && docker pull 10.22.1.1:5000/fabric-frontend:anonymous-dev && docker pull 10.22.1.1:5000/fabric-peer:anonymous-dev && docker pull 10.22.1.1:5000/fabric-tools:anonymous-dev"
bash all_cmd.sh "docker pull 10.22.1.1:5000/fabric-orderingnode:anonymous-dev && docker pull 10.22.1.1:5000/fabric-frontend:anonymous-dev && docker pull 10.22.1.1:5000/fabric-peer:anonymous-dev && docker pull 10.22.1.1:5000/fabric-tools:anonymous-dev"
