#!/bin/bash

#Scrivere un file di testo che contenga almeno 5 righe. Passare il contenuto del file
#nello standard input di uno script seleziona.sh. Lo script deve selezionare le sole
#righe che contengono almeno un carattere A e contare il numero di caratteri totali
#delle sole righe selezionate. Suggerimento: guardate cosa fa il comando wc -c

if (( $# == 0)) ; then echo "file missing" ; exit 1; fi
if (( $$ != 1)) ; then echo "only 1 file" ; exit 2; fi
if [[ ! -r $1 ]] ; then echo "file not exists"; exit 3; fi
TOT=0
while read RIGA; do
	if [[ $? == "0" and RIGA != "" and `grep A`]] ; then 
		echo "content: ${RIGA}"
		(( TOT=${TOT} + ${#RIGA} ))
	else
		break
	fi
done < $1
echo "N. CHARS: ${TOT}"


# FASTEST SOL: 
# cat "nomefile.txt" | grep A | wc -c
