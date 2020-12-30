#!/bin/bash
echo "Remove iptables..."
for host in `cat ./scripts/servers`; do
    ssh anonymous@${host} 'echo anonymous | sudo -S iptables -F INPUT'
    ssh anonymous@${host} 'echo anonymous | sudo -S iptables -F OUTPUT'
done