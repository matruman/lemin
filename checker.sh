#!/bin/bash
i=0
result=0
gen=0
while [ 1 ]
do
	#gen=$(./generator --flow-one> checker_map; cat checker_map | grep "#Here is the number of lines required" | tail -n 1 | cut -d " " -f8 | bc)
	#gen=$(./generator --flow-ten> checker_map; cat checker_map | grep "#Here is the number of lines required" | tail -n 1 | cut -d " " -f8 | bc)
	#gen=$(./generator --flow-thousand> checker_map; cat checker_map | grep "#Here is the number of lines required" | tail -n 1 | cut -d " " -f8 | bc)
	#gen=$(../maps_lemin/generator --big> checker_map; cat checker_map | grep "#Here is the number of lines required" | tail -n 1 | cut -d " " -f8 | bc)
	gen=$(../maps_lemin/generator --big-superposition > checker_map$i; cat checker_map$i | grep "#Here is the number of lines required" | tail -n 1 | cut -d " " -f8 | bc)
	./lem-in < checker_map$i > checker_map_lem_in
	my_lem_in=$(cat checker_map_lem_in | grep "^L[0-9]" | wc -l | bc)
	result=$(($result + $my_lem_in - $gen))
	i=$(($i + 1))
	echo "#$i lem-in $my_lem_in, generator $gen, time $time"
done
