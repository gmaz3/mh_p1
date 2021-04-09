#!/bin/bash

directorio="datos"

for i in $(ls $directorio)
do
    echo $i
    ./greedy 'datos/'$i
done
