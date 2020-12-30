# Sequencer

# Workflow
1. Client sends messages to sequencer;
2. Sequencer inserts sequence number to messages, and broadcasts messages to 10.22.1.255:9999 (i.e., all servers in our cluster);
3. Servers receive ordered messages.

# Compile Sequencer

```bash
g++ -std=c++11 sequencer.cpp
```

# Test Sequencer

Run sequencer:
```bash
# bind with locahost:8888 
./sequencer > log 
# tps
grep "tps" log
```

Run server:
```bash
./server # bind with localhost:9999
```

Run client:
```bash
# suppose 10.22.1.6 is the sequencer address
./client 10.22.1.6

# read from file and repeatly send to sequencer 
go run udpClient.go --host 10.22.1.6 --file filename
```

