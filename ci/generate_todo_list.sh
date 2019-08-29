#!/bin/bash

echo "# TODO List\n" > TODO.md

TODOS=$(git grep -EIn "TODO" src/ include/)

while read -r line; 
do
	line=${line//$"//"/}
	echo " - [ ] ${line}\n" >> TODO.md
done <<< "$TODOS"

