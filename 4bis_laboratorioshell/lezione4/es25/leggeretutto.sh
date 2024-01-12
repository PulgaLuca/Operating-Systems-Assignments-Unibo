#!/bin/bash

#Scaricare il file di testo
#http://www.cs.unibo.it/~ghini/didattica/sistemioperativi/ESERCIZI/miofileNoNL.txt
#che ha anche delle righe vuote e che termina con una riga che non ha il
#carattere di andata a capo. Scrivere poi uno script leggitutto.sh che legga riga
#per riga quel file e stampi a video ciascuna riga letta, compresa l'ultima.

exec {FD}< ./miofileNoNL.txt
if (( $? == 0 )) ; then
	while read -u ${FD} RIGA ; do
		if [[ $? == 0 || ${RIGA} != "" ]] ; then
			echo "${RIGA}"
		fi
	done
	exec {FD}>&-
fi

