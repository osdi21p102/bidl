#!/bin/bash

echo "#!/bin/bash" > start-sendTransaction.sh

for i in `seq 20`; do
    echo "###  10.22.1.$i  ###"
    ssh anonymous@10.22.1.$i "$@"  > temp__ 2>&1
    cat temp__ | grep "hlf-client" | awk '{print $1}' | while read x; do
        echo "ssh anonymous@10.22.1.$i docker exec -d $x bash sendTransaction.sh " >> start-sendTransaction.sh
    done
    rm temp__
done

cat start-sendTransaction.sh

