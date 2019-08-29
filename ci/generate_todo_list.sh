#!/bin/sh

echo "# TODO List\n" > TODO.md

TODOS=$(git grep -EIn "TODO" src/ include/)

while read -r line in $TODOS
do
	line=${line//$"//"/}
	echo " - [ ] ${line}\n" >> TODO.md
done <<< "$TODOS"

