#!/bin/bash

for i in `seq 20`; do
    echo "###  10.22.1.$i  ###"
    ssh anonymous@10.22.1.$i "$1" 
done

echo done

