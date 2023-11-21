#!/bin/bash
name=$1;
if [[ -f ${name} && ${#name} -lt 30 ]] ;
then
	echo "${name} has less than 30 chars";
else
	echo "${name} has more than 30 chars";
fi;
