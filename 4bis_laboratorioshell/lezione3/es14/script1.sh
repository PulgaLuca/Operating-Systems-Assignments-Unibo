#!/bin/bash
PARAMS=1
while (( ${PARAMS} <= $# ))
do
	echo "arg: ${PARAMS} is ${!PARAMS}"
	(( PARAMS=${PARAMS}+1 ))
done
source ./script2.sh
