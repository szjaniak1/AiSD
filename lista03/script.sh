#!/usr/sbin/zsh

declare datafile=./data/results.csv
rm $datafile

echo "type;n;comp;shifts" >> $datafile

for n in {100..10000..100}
do
	for m in {1..10}
	do
		echo "$(./rNG.o $n | ./zad1.out)" >> $datafile
	done
done
