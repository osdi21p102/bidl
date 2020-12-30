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

docker run --rm --network=HLF --name=bft.frontend.1000 bftsmart/fabric-frontend:amd64-1.3.0 1000 > logs/frontend1.log 2>&1 &
docker run --rm --network=HLF --name=bft.frontend.2000 bftsmart/fabric-frontend:amd64-1.3.0 2000 > logs/frontend2.log 2>&1 &
