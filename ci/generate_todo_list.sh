#!/bin/sh

echo -e "# TODO List\n" > TODO.md

TODOS=$(git grep -EIn "TODO" src/ include/)

while read -r line in $'TODOS'
do
	line=${line//$"//"/}
	echo -e " - [ ] $line\n" >> TODO.md
done <<< $'TODOS' 

