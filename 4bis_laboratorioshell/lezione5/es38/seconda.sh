#!/bin/bash

#Scrivere un file contenente alcune (almeno 5) righe di testo, ciascuna con almeno 4
#parole. Scrivere uno script seconda.sh che prende come unico argomento il nome
#di quel file. Dentro lo script utilizzare ripetutamente il comando read per leggere la
#seconda parola di ogni riga del file. Tutte le seconde parole devono essere
#concatenata in una variabile di nome OUT. Alla fine dello script, la variabile OUT
#deve essere visualizzata sullo standard output.

if (( $# != 1 )) ; then echo "Insert a single file name" ; exit 1 ; fi
if [[ ! -r $1 ]] ; then echo "Insert a readable file" ; exit 1 ; fi
OUT=""
while read F S T ; do
	OUT=${OUT}" "${S}
done<$1
echo "${OUT}"



