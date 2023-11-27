#!/bin/bash

PROD=1
NUM=1
while (( ${NUM} <= $1 ))
do
	(( PROD=${PROD}*${NUM} ))
	(( NUM=${NUM}+1 ))
done
echo ${PROD}
