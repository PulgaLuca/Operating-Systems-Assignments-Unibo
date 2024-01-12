#!/bin/bash

while (( 1 )) ; do
	read F
	if [[ $? == 0  || ${F} != "" ]] ; then
		echo ${F}
	fi 
done
