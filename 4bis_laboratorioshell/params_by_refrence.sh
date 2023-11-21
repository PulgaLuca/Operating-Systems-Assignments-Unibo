#!/bin/bash
echo "n params: $#"
echo "params: $*"
echo "process name: $0"

NUM=1
while (( ${NUM} <= $# ))
do
	echo "arg ${NUM} is ${!NUM}"
	((NUM=${NUM}+1))
done
echo "exit status: $?"
