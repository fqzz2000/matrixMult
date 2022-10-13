#!/bin/bash
count=1
for i in ./testcase*
do
    echo "Running test $count" 
    ./MatrixMul $i/matrix1.txt $i/matrix2.txt 
    echo 
    count=$(($count+1))
done


