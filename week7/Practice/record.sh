#!/bin/bash

file="record.log"
# delete the origin file
if test -f $file;
then
	rm $file
fi

# the number of thread
for i in {1..5}
do
	# the parameter 'n'
	for j in {1..10}
	do
		# run 3 times
		echo -n -e "$i\t$j\t" >> $file
		for k in {1..500}
		do
			./fib_v4 $j $i >> $file
			echo -n -e ' ' >> $file
		done
		# new line
		echo "" >> $file
	done
done

cat $file
