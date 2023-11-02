#!/bin/bash

set -xe

if [[ $# -ne 2 ]]; then
	echo "Usage: $0 [digraph|trigraph] <filename>"
	exit 1
fi

while IFS= read -r line; do
	[[ -z "$line" ]] && continue
	IFS=' ' read -r -a values <<< "$line"

	type="${values[0]}"
	input="${values[1]}"
	output="${values[2]}"

	if [[ $1 == "digraph" ]]; then
		./digraph -t $type -i $input -o $output.png
	elif [[ $1 == "trigraph" ]]; then
		./trigraph -t $type -i $input -o $output.pc
	else
		echo "Invalid argument: $1"
		exit 1
	fi
done < $2
