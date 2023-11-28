#!/bin/bash

#Scrivere uno script bash leggere.sh che legge le righe del file /usr/include/stdio.h
#e stampa a video la sola terza parola di ciascuna riga, o niente se la terza parola
#non esiste

exec {FD}<"~/usr/include/stdio.h"
if (($?==0));then
	while read -U ${FD} A B C ; do
		echo "${C}"
	done
	exec {FD}>&-
fi
