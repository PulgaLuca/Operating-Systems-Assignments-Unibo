#!/bin/bash
PARAMS=$#
while(( ${PARAMS} > 0))
do
	echo "arg reverted ${PARAMS} is ${!PARAMS}"
	(( PARAMS=${PARAMS}-1 ))
done
echo "finished"

