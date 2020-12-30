Run HLF with BFT-Smart ordering service.
# Run Single Host Example

Configure all materials needed for peer, frontend, and orderer.

4 peers + 2 frontends + 4 orderer:

```shell
cd hlf_config/scripts
bash channel-config.sh
```

Start nodes:

```shell
bash start_all.sh
```

Set TPS evaluation parameters:
```shell
vim hlf_config/scripts/scripts/tpsConfig.yaml
```

Initialize fabric-network and evaluate TPS:
```shell
docker attach cli
bash scripts/script.sh
peer chaincode tps # start TPS evaluation according scripts/tpsConfig.yaml, try to modify config and re-execute.
```

Stop nodes:

```shell
bash kill_all.sh
```

# Results

About 3000 tps