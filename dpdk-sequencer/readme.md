How to run dpdk-sequencer with Ethernet:

1. ssh onto the server, and go to the dpdk installation directory
2. cd xxx/dpdk-sequencer/dpdk/usertools
3. sudo su
4. ./dpdk-setup.sh
5. choose 12 to build x86_64-native-linuxapp-gcc
6. choose 15 to Insert IGB UIO module
7. choose 18 to Setup hugepage mappings for non-NUMA systems. Enter 1280
8. ssh onto the same server from another terminal and then `sudo ifconfig eno1 down; sudo ifconfig eno2 down`
9. back to the original terminal and choose 21 to Bind Ethernet/Crypto device to IGB UIO module. Enter 00:1f.6
11. choose 21 again to Bind Ethernet/Crypto device to IGB UIO module. Enter 05:00.0
12. choose 25. Enter f.
13. Enter `set fwd udpecho` 
14. Enter `start`

To clear the sequence number.
1. Enter `quit`
2. choose 25, Enter f
3. Enter `set fwd udpecho` 
4. Enter `start`

How to run dpdk-sequencer with Mellanox:
1. ssh onto the server, and go to the dpdk installation directory
2. cd xxx/dpdk-sequencer/dpdk/usertools
3. sudo su
4. ./dpdk-setup.sh
5. choose 12 to build x86_64-native-linuxapp-gcc
6. choose 18 to Setup hugepage mappings for non-NUMA systems. Enter 1280
7. ssh onto the same server from another terminal and then `sudo ifconfig enp1s0d1 down`
8. back to the original terminal and choose 25. Enter f
9. Enter `set fwd udpecho` 
10. Enter `start`

The source code of sequencer is in dpdk/app/test-pmd/icmpecho.c
