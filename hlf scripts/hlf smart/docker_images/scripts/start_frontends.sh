#!/bin/bash

# if grep -q "Ready to process operations" "./logs/orderer1.log"; then
#   echo "contains" # SomeString was found
# fi

echo "###################################"
echo "Start frontend..."
echo "###################################"

until grep -q "Ready to process operations" "./logs/orderer1.log"
do
  echo "Ording nodes are not ready"
  sleep 1
done

echo "Ordering nodes are ready."

docker run --rm --network=HLF --name=1000.frontend.bft -e FRONTEND_CONFIG_DIR=/bft-config/config/ -e FABRIC_CFG_PATH=/bft-config/fabric/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/frontend_material/:/bft-config/  bftsmart/fabric-frontend:amd64-1.3.0 1000 > logs/frontend1000.log 2>&1 &
docker run --rm --network=HLF --name=2000.frontend.bft -e FRONTEND_CONFIG_DIR=/bft-config/config/ -e FABRIC_CFG_PATH=/bft-config/fabric/ -v /home/anonymous/Github/fabric-orderingservice/docker_images/frontend_material/:/bft-config/  bftsmart/fabric-frontend:amd64-1.3.0 2000 > logs/frontend2000.log 2>&1 &
