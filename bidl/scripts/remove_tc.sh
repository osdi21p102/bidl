#!/bin/bash
echo "Remove traffic control..."
for host in `cat ./scripts/servers`; do
    ssh anonymous@${host} 'echo anonymous | sudo -S tc qdisc del dev enp5s0 root'
done