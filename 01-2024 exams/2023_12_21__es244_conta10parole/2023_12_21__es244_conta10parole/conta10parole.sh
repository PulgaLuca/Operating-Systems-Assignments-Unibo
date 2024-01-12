#!/bin/bash

# stampare a video il numero di parole "int" totali
# trovate tra le prime 10 parole di ciascuna riga
# del file ./prova.txt
# Attenzione, le parole che includono int non vanno contate.
# Ad esempio, le parole inta e bint non vanno contate.
# Il file passato come argomento ha 9 di queste parole int
# percio' lo script deve stampare a video 9

CONT=0
while read P0 P1 P2 P3 P4 P5 P6 P7 P8 P9; do
	for (( i=0; ${i}<10;i=${i}+1 )) ; do
		INDEX=P${i}
		if [[ ${!INDEX} == "int" ]] ; then
			(( CONT=${CONT}+1 ))	
		fi
	done
done < ./prova.txt
echo ${CONT}
