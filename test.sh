#!/bin/bash
sum=0
for i in {1..25}
do
	./bin/runner.o result.txt
	var=$(tail -1 ./result.txt | awk '{print $NF}')
	sum=$(perl -E "say $sum+$var")
done


perl -E "say $sum/25"
