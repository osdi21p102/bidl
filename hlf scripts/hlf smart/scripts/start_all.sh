#!/bin/bash

rm -rf logs
mkdir logs

bash ./scripts/start_orderers.sh
bash ./scripts/start_frontends.sh
bash ./scripts/start_peers.sh