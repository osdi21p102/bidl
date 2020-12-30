#!/bin/bash
# Suppose 10.22.1.1 is the address of the docker registry server address 

docker tag hyperledger/fabric-tools:latest 10.22.1.1:5000/fabric-tools:anonymous
docker tag hyperledger/fabric-peer:latest 10.22.1.1:5000/fabric-peer:anonymous
docker tag hyperledger/fabric-orderer:latest 10.22.1.1:5000/fabric-orderer:anonymous

docker push 10.22.1.1:5000/fabric-tools:anonymous
docker push 10.22.1.1:5000/fabric-peer:anonymous
docker push 10.22.1.1:5000/fabric-orderer:anonymous


ssh anonymous@10.22.1.1 "docker pull 10.22.1.1:5000/fabric-tools:anonymous && docker pull 10.22.1.1:5000/fabric-orderer:anonymous && docker pull 10.22.1.1:5000/fabric-peer:anonymous"
bash all_cmd.sh "docker pull 10.22.1.1:5000/fabric-tools:anonymous && docker pull 10.22.1.1:5000/fabric-orderer:anonymous && docker pull 10.22.1.1:5000/fabric-peer:anonymous"
