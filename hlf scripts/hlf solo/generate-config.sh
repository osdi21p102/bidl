#!/bin/zsh

work_path=$(dirname $(readlink -f $0))
echo "work_path is $work_path"
cd $work_path

echo anonymous | sudo -S rm -rf ~/share_cluster/fabric_cluster/*
exit 1

# clear the old X.509
rm -rf crypto-config
mkdir crypto-config
rm -rf channel-artifacts
mkdir channel-artifacts

# generate X.509 using the default configuration
cryptogen generate --config=crypto-config.yaml

# tell the tool where to look for the configtx.yaml
export FABRIC_CFG_PATH=$PWD
export CHANNEL_NAME=mychannel

# create the orderer genesis block
configtxgen -profile OneOrgsOrdererGenesis -outputBlock ./channel-artifacts/genesis.block  #-channelID $CHANNEL_NAME

# create a channel configuration transaction
configtxgen -profile OneOrgsChannel -outputCreateChannelTx ./channel-artifacts/channel.tx -channelID $CHANNEL_NAME

# define the anchor peer for Org1
configtxgen -profile OneOrgsChannel -outputAnchorPeersUpdate ./channel-artifacts/Org1MSPanchors.tx -channelID $CHANNEL_NAME -asOrg Org1MSP

# Rename the key files we use to be key.pem instead of a uuid
for KEY in $(find crypto-config -type f -name "*_sk"); do
    KEY_DIR=$(dirname ${KEY})
    mv ${KEY} ${KEY_DIR}/key.pem
done


# Copy the chaincode, crypto-config and channel-artifacts to the NFS directory, which is shared on all swarm nodes, HLF peers on all nodes can read them.
echo anonymous | sudo -S cp -rf ../FabricClient /home/anonymous/share_cluster/fabric_cluster/
echo anonymous | sudo -S cp -rf ./crypto-config /home/anonymous/share_cluster/fabric_cluster/
echo anonymous | sudo -S cp -rf ./channel-artifacts /home/anonymous/share_cluster/fabric_cluster/
echo anonymous | sudo -S cp -rf ./chaincode /home/anonymous/share_cluster/fabric_cluster/
echo anonymous | sudo -S cp -rf ./scripts /home/anonymous/share_cluster/fabric_cluster/
echo anonymous | sudo -S cp -rf network.yaml /home/anonymous/share_cluster/fabric_cluster/
echo anonymous | sudo -S cp -rf sendTransaction.sh /home/anonymous/share_cluster/fabric_cluster/
