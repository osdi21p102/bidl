#!/bin/bash
ssh anonymous@10.22.1.5 docker exec -d 860e9f571dea bash sendTransaction.sh 
ssh anonymous@10.22.1.13 docker exec -d 30a9b288f2aa bash sendTransaction.sh 
ssh anonymous@10.22.1.15 docker exec -d 3ca50e320ad4 bash sendTransaction.sh 
ssh anonymous@10.22.1.17 docker exec -d 1098229cb694 bash sendTransaction.sh 
ssh anonymous@10.22.1.20 docker exec -d ed70ec566755 bash sendTransaction.sh 
