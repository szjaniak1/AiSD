#!/usr/sbin/zsh

rm ./data/sortingAlgResults.csv
declare -a algorithms=("./sortingAlg/qS.o" "./sortingAlg/mS.o" "./sortingAlg/iS.o" "./sortingAlg/dPQS.o" "./sortingAlg/cS.o")
declare -a algNames=("quicksort" "mergesort" "insertionsort" "dualpivotquicksort" "customsort")
datafile="./data/sortingAlgResults.csv"
declare -i i=1

echo "type;n;comp;shifts" >> $datafile

for alg in ${algorithms[@]}
do
	for n in {10..200..10}
	do
		for k in 1 10 100
		do
			for k1 in $(seq 1 $k)
			do
				echo "${algNames[$i]};$n;$(../zad1/generators/rNG.o $n | $alg);" >> $datafile
			done
		done
	done
	i=$(( $i + 1))
done

i=0

for alg in ${algorithms[@]}
do
	if [ $alg != "./sortingAlg/iS.o" ] 
	then
		for n in {1000..20000..1000}
		do
			for k in 1 10 100
			do
				for k1 in $(seq 1 $k)
				do
					echo "${algNames[$i]};$n;$(../zad1/generators/rNG.o $n | $alg);" >> $datafile
				done
			done
		done
	fi
	i=$(( $i + 1))
done
