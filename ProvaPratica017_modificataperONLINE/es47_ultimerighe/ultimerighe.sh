#!/bin/bash
FILE=$1
if [[ "$#" != 1 ]] ; then
	echo "numero argomenti errato" 1>&2
	exit 1
else
	if [[ ! -e ${FILE} ]] ; then
		echo "argomento non file" 1>&2
		exit 2
	else
		(sleep 2 ; tail -n 3 ${FILE} >> ./OUTPUT.TXT ; exit 0 ) &
		echo DONE OK
	fi
fi
