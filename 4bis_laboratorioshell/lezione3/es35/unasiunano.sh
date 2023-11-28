#!/bin/bash

#Scrivere uno script unasiunano.sh che prende delle righe di testo dallo standard
#input e visualizza le righe una si ed una no
PARITY=1
while read RIGA ; do
	if(( ${PARITY} == 1  )) ; then
		(( PARITY=0 ))
		echo "${RIGA}"
	else
		(( PARITY=1 ))
		echo "skip"
	fi
done
