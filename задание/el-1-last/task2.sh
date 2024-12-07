#!/bin/bash

declare -A matrix

all=$(cat $(find lists/ -name '*.src') | grep ".src$" -v | sort | uniq);

w="0"
for filename in $all
do
	strlen=${#filename}
	if [ "$strlen" -gt "$w" ]
	then
		w="$strlen"
	fi
done

format="%-${w}s"

for filename in $all
do
	printf $format $filename
done

printf "\n"

for filename in $all
do
	while read -r line
	do
		if [ "$line" != "\"" ] && [ "$line" != "DEPEND=\"" ]
		then
			matrix["$line"]=1
		fi
	done < deps/"$filename".deps
	
	printf $format "$filename "
	for filename2 in $all:
	do
		if [ -v matrix[$filename2] ]
		then
			printf $format "1"
		else
			printf $format "0"
		fi
	done
	printf "\n"
	
done
