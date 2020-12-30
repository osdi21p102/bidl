#!/bin/bash

CHANNEL_NAME="$1"
DELAY="$2"
LANGUAGE="$3"
TIMEOUT="$4"
VERBOSE="$5"
: ${CHANNEL_NAME:="mychannel"}
: ${DELAY:="5"}
: ${LANGUAGE:="golang"}
: ${TIMEOUT:="50"}
: ${VERBOSE:="true"}
LANGUAGE=`echo "$LANGUAGE" | tr [:upper:] [:lower:]`
COUNTER=1
MAX_RETRY=10

CC_SRC_PATH="github.com/chaincode/smallbank/go/"

echo "Channel name : "$CHANNEL_NAME

# import utils
. scripts/utils.sh

peer chaincode tps

exit 0
