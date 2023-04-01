#!/usr/sbin/zsh

rm ./data/sortingAlgResults.csv
declare -a algorithms=("./sortingAlg/qS.o" "./sortingAlg/mS.o" "./sortingAlg/iS.o")
datafile="./data/sortingAlgResults.csv"

for n in {10..200..10}
do
	echo -n ";$n;$n" >> $datafile
done

echo "" >> $datafile

for alg in ${algorithms[@]}
do
	for k in 1 10 100
	do
		for k1 in $(seq 1 $k)
		do
			echo -n "$k;" >> $datafile
			for n in {10..200..10}
			do
				echo -n "$(../zad1/generators/rNG.o $n | $alg);" >> $datafile
			done
			echo "" >> $datafile
		done
	done
done

for n in {1000..20000..1000}
do
	echo -n ";$n;$n" >>$datafile
done

echo "" >> $datafile

for alg in ${algorithms[@]}
do
	if [ $alg != "./sortingAlg/iS.o" ] 
	then
		for k in 1 10 100
		do
			for k1 in $(seq 1 $k)
			do
				echo -n "$k;" >> $datafile
				for n in {1000..20000..1000}
				do
					echo -n "$(../zad1/generators/rNG.o $n | $alg);" >> $datafile
				done
				echo "" >> $datafile
			done
		done
	fi
done
