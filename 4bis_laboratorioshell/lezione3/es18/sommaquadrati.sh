#!/bin/bash

#Scrivere uno script bash sommaquadrati.sh che prende in input un numero
#qualsiasi di argomenti interi positivi e stampa a video il numero intero dato dalla
#somma dei quadrati dei singoli argomenti diminuito della somma degli indici degli
#argomenti.
RIS=0
for ((NUM=1;${NUM}<=$#;NUM=${NUM}+1)) ; do 
	(( RIS=${RIS}+${!NUM}*${!NUM} ))
	(( RIS=${RIS}-${NUM} ))
done
echo "Ris: ${RIS}"
