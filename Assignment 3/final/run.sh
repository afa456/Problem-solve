#!/bin/bash

for((i=10000;i<31000;i+=1000)); do
	echo $i
	./test.o "./output/Graph_$i.txt" -o "./output/out_Graph_$i.txt"
	
done

