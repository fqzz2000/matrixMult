#!/bin/bash
count=1
for i in ./testcase*
do
    echo "Running the $count 's test" 
    ./MatrixMul $i/matrix1.txt $i/matrix2.txt 
    echo 
    count=$(($count+1))
done


