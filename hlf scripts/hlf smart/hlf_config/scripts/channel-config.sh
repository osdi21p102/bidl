#!/bin/bash
work_path=$(dirname $(readlink -f $0))
echo "work_path is $work_path"
cd $work_path

# clear the old X.509
rm -rf crypto-config
mkdir crypto-config
rm -rf channel-artifacts
mkdir channel-artifacts
echo anonymous | sudo -S rm -rf /home/anonymous/share_cluster/fabric_cluster/*

# generate X.509 using the default configuration
cryptogen generate --config=crypto-config.yaml

# tell the tool where to look for the configtx.yaml
export FABRIC_CFG_PATH=$PWD
export CHANNEL_NAME=mychannel

# create the orderer genesis block
configtxgen -profile BFTGenesis -outputBlock ./channel-artifacts/genesisblock
cp ./channel-artifacts/genesisblock ./channel-artifacts/genesis.block
configtxgen -profile BFTChannel -outputCreateChannelTx channel-artifacts/channel.tx -channelID mychannel
configtxgen -profile BFTChannel -outputAnchorPeersUpdate channel-artifacts/anchor.tx -channelID mychannel -asOrg IBM


# Rename the key files we use to be key.pem instead of a uuid
for KEY in $(find crypto-config -type f -name "*_sk"); do
    KEY_DIR=$(dirname ${KEY})
    mv ${KEY} ${KEY_DIR}/key.pem
done

# collect keys for ordering nodes and frontends
rm -rf $work_path/keys
mkdir $work_path/keys

cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/0.node.bft/msp/signcerts/0.node.bft-cert.pem $work_path/keys/cert0.pem
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/1.node.bft/msp/signcerts/1.node.bft-cert.pem $work_path/keys/cert1.pem
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/2.node.bft/msp/signcerts/2.node.bft-cert.pem $work_path/keys/cert2.pem
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/3.node.bft/msp/signcerts/3.node.bft-cert.pem $work_path/keys/cert3.pem

cp $work_path/crypto-config/ordererOrganizations/frontend.bft/orderers/1000.frontend.bft/msp/signcerts/1000.frontend.bft-cert.pem $work_path/keys/cert1000.pem
cp $work_path/crypto-config/ordererOrganizations/frontend.bft/orderers/2000.frontend.bft/msp/signcerts/2000.frontend.bft-cert.pem $work_path/keys/cert2000.pem


############################ orderers ##########################################
rm -rf $work_path/orderer0_material
mkdir -p $work_path/orderer0_material/config/keys
# copy genesisblock
cp $work_path/channel-artifacts/genesisblock $work_path/orderer0_material
# copy config files
cp -r $work_path/materials/orderer/* $work_path/orderer0_material/config
# copy keys
cp -r $work_path/keys/* $work_path/orderer0_material/config/keys
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/0.node.bft/msp/keystore/key.pem $work_path/orderer0_material/config/keys/keystore.pem

rm -rf $work_path/orderer1_material
mkdir -p $work_path/orderer1_material/config/keys
# copy genesisblock
cp $work_path/channel-artifacts/genesisblock $work_path/orderer1_material
# copy config files
cp -r $work_path/materials/orderer/* $work_path/orderer1_material/config
# copy keys
cp -r $work_path/keys/* $work_path/orderer1_material/config/keys
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/1.node.bft/msp/keystore/key.pem $work_path/orderer1_material/config/keys/keystore.pem

rm -rf $work_path/orderer2_material
mkdir -p $work_path/orderer2_material/config/keys
# copy genesisblock
cp $work_path/channel-artifacts/genesisblock $work_path/orderer2_material
# copy config files
cp -r $work_path/materials/orderer/* $work_path/orderer2_material/config
# copy keys
cp -r $work_path/keys/* $work_path/orderer2_material/config/keys
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/2.node.bft/msp/keystore/key.pem $work_path/orderer2_material/config/keys/keystore.pem

rm -rf $work_path/orderer3_material
mkdir -p $work_path/orderer3_material/config/keys
# copy genesisblock
cp $work_path/channel-artifacts/genesisblock $work_path/orderer3_material
# copy config files
cp -r $work_path/materials/orderer/* $work_path/orderer3_material/config
# copy keys
cp -r $work_path/keys/* $work_path/orderer3_material/config/keys
cp $work_path/crypto-config/ordererOrganizations/node.bft/orderers/3.node.bft/msp/keystore/key.pem $work_path/orderer3_material/config/keys/keystore.pem

############################ frontends ########################################
rm -rf $work_path/frontend1000_material
mkdir -p $work_path/frontend1000_material/config/keys
mkdir -p $work_path/frontend1000_material/fabric
# copy genesisblock
cp $work_path/channel-artifacts/genesisblock $work_path/frontend1000_material
# copy config files
cp -r $work_path/materials/frontend/* $work_path/frontend1000_material/config
# copy keys
cp -r $work_path/keys/* $work_path/frontend1000_material/config/keys
cp $work_path/crypto-config/ordererOrganizations/frontend.bft/orderers/1000.frontend.bft/msp/keystore/key.pem $work_path/frontend1000_material/config/keys/keystore.pem
# copy fabric folder
cp -r $work_path/materials/frontend/orderer.yaml $work_path/frontend1000_material/fabric 
cp -r $work_path/crypto-config/ordererOrganizations/frontend.bft/orderers/1000.frontend.bft/msp $work_path/frontend1000_material/fabric/


rm -rf $work_path/frontend2000_material
mkdir -p $work_path/frontend2000_material/config/keys
mkdir -p $work_path/frontend2000_material/fabric
# copy genesisblock
cp $work_path/channel-artifacts/genesisblock $work_path/frontend2000_material
# copy config files
cp -r $work_path/materials/frontend/* $work_path/frontend2000_material/config
# copy keys
cp -r $work_path/keys/* $work_path/frontend2000_material/config/keys
cp $work_path/crypto-config/ordererOrganizations/frontend.bft/orderers/2000.frontend.bft/msp/keystore/key.pem $work_path/frontend2000_material/config/keys/keystore.pem
# copy fabric folder
cp -r $work_path/materials/frontend/orderer.yaml $work_path/frontend2000_material/fabric 
cp -r $work_path/crypto-config/ordererOrganizations/frontend.bft/orderers/2000.frontend.bft/msp $work_path/frontend2000_material/fabric/

############################ peers ########################################
rm -rf $work_path/peer0_material
mkdir -p $work_path/peer0_material/fabric
# copy config files
cp -r $work_path/materials/peer/core.yaml $work_path/peer0_material/fabric
# copy msp
cp -r $work_path/crypto-config/peerOrganizations/ibm.bft/peers/0.peer.ibm.bft/msp $work_path/peer0_material/fabric/

rm -rf $work_path/peer1_material
mkdir -p $work_path/peer1_material/fabric
# copy config files
cp -r $work_path/materials/peer/core.yaml $work_path/peer1_material/fabric
# copy msp
cp -r $work_path/crypto-config/peerOrganizations/ibm.bft/peers/1.peer.ibm.bft/msp $work_path/peer1_material/fabric/

rm -rf $work_path/peer2_material
mkdir -p $work_path/peer2_material/fabric
# copy config files
cp -r $work_path/materials/peer/core.yaml $work_path/peer2_material/fabric
# copy msp
cp -r $work_path/crypto-config/peerOrganizations/ibm.bft/peers/2.peer.ibm.bft/msp $work_path/peer2_material/fabric/

rm -rf $work_path/peer3_material
mkdir -p $work_path/peer3_material/fabric
# copy config files
cp -r $work_path/materials/peer/core.yaml $work_path/peer3_material/fabric
# copy msp
cp -r $work_path/crypto-config/peerOrganizations/ibm.bft/peers/3.peer.ibm.bft/msp $work_path/peer3_material/fabric/

############################ client ########################################

rm -rf $work_path/cli0_material
mkdir -p $work_path/cli0_material/fabric
# copy config files
cp -r $work_path/materials/cli/core.yaml $work_path/cli0_material/fabric
# copy msp
cp -r $work_path/crypto-config/peerOrganizations/ibm.bft/users/User1@ibm.bft/msp $work_path/cli0_material/fabric/
cp -r $work_path/crypto-config $work_path/cli0_material/fabric/
# copy chaincode
cp -r $work_path/chaincode $work_path/cli0_material/fabric
# copy channel creation files
cp $work_path/channel-artifacts/* $work_path/cli0_material/fabric
cp $work_path/configtx.yaml $work_path/cli0_material/fabric
cp $work_path/script.sh $work_path/cli0_material/

cp -r orderer0_material ~/share_cluster/fabric_cluster
cp -r orderer1_material ~/share_cluster/fabric_cluster
cp -r orderer2_material ~/share_cluster/fabric_cluster
cp -r orderer3_material ~/share_cluster/fabric_cluster

cp -r peer0_material ~/share_cluster/fabric_cluster
cp -r peer1_material ~/share_cluster/fabric_cluster
cp -r peer2_material ~/share_cluster/fabric_cluster
cp -r peer3_material ~/share_cluster/fabric_cluster

cp -r frontend1000_material ~/share_cluster/fabric_cluster
cp -r frontend2000_material ~/share_cluster/fabric_cluster

cp -r crypto-config ~/share_cluster/fabric_cluster
cp -r channel-artifacts ~/share_cluster/fabric_cluster
