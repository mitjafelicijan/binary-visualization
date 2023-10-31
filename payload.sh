#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <filename>"
	exit 1
fi

while IFS= read -r line; do
	[[ -z "$line" ]] && continue
	IFS=' ' read -r -a values <<< "$line"

	type="${values[0]}"
	input="${values[1]}"
	output="${values[2]}"

	./digraph -t $type -i $input -o $output
done < $1
