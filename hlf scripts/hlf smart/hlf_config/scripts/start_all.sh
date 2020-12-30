#!/bin/bash

rm -rf logs
mkdir logs

docker-compose -f docker-compose.yaml up -d 
