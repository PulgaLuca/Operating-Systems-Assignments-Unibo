#!/bin/bash

while read NAME SURNAME MAT VOTO ; do 
	if (( ${VOTO} < "18" )) ; then
		FIRST=`grep ${MAT} prova1.txt`
		if [[ -z ${FIRST} ]] ; then 
			echo "${MAT} ${SURNAME} ${NAME} ${VOTO}"
		fi
	fi
done < prova2.txt
