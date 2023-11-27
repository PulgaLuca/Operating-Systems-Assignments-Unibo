#!/bin/bash
ARGS=1
EVEN=""
ODD=""
while (( ${ARGS} <= "$#" ))
do
	if (( ${ARGS}%2==0 ))
	then
		EVEN=${EVEN}" "${!ARGS}
	else
		ODD=${ODD}" "${!ARGS}
	fi
	(( ARGS=${ARGS}+1 )) 
done
echo ${EVEN}${ODD}
