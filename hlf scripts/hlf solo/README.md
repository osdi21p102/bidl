# Hyperledger Fabric Code
Fabric version: https://github.com/anonymous-J/HLF

# Build Image
```shell
git clone https://github.com/anonymous-J/HLF $GOPATH/src/github.com/hyperledger/fabric
cd $GOPATH/src/github.com/hyperledger/fabric
make peer-docker orderer-docker tools-docker
```

# Deploy

```bash
# scp images to all servers
bash tag.sh

# run with docker-compose.yaml
bash run.sh 
```

# Test throughput
Modify client configuration file: scripts/tpsConfig.yaml

```bash
bash send.sh
```


# Stop
```shell
bash stop.sh
```




