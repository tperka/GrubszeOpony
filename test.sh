#!/bin/bash
sum=0
count=0
for i in {1..25}
do
	./bin/runner.o
	var=$(tail -1 ./result.txt | awk '{print $NF}')
	echo "$var"
	sum=$(perl -E "say $sum+$var")
	echo "$sum"
	$((count++))
done


echo $count
perl -E "say $sum/$count"
