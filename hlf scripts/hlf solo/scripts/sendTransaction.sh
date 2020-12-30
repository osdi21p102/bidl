#!/bin/bash

workload=$1

CHANNEL_NAME=mychannel
. scripts/utils.sh


while read item; do
    #echo $item

    endorseAbort 0 1 $item &
done < $workload
