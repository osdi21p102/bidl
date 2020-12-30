#!/bin/bash

item=$1
CHANNEL_NAME=mychannel

. scripts/utils.sh

chaincodeQuery 0 1 $1
