#!/usr/sbin/zsh

#select with different stat
declare datafile=./data/select_data.csv
rm $datafile
echo "type;n;k;comp;swaps" >> $datafile

for n in {100..10000..100}
do
	for k in 0 $n/4 $n/2 $n-1
	do
		for m in {1..100}
		do
			echo "select;$n;$k;$(./rNG.o $n | ./zad1.out 2 $k 5)" >> $datafile
		done
	done
done

#select with different size
declare datafile=./data/container_size_data.csv
rm $datafile
echo "size;n;k;comp;swaps" >> $datafile
for size in 3 5 7 9
do
	for n in {100..10000..100}
	do
		for k in 0 $n/4 $n/2 $n-1
		do
			for m in {1..0100}
			do
				echo "select;$n;$k;$(./rNG.o $n | ./zad1.out 2 $k $size)" >> $datafile
			done
		done
	done
done

#binary search
declare datafile=./data/bin_search_data1.csv
rm $datafile
echo "target;n;comp;time" >> $datafile
for n in {1000..100000..1000}
do
	for m in {0..1000}
	do
		echo "3;$n;" >> $datafile
	done

	for m in {0..1000}
	do
		echo "$($n/12);$n;comp;" >> $datafile
	done


done

