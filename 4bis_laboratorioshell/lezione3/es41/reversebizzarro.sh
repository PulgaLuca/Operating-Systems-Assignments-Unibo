#!/bin/bash

#Scrivere uno script reversebizzarro.sh che prende una stringa come unico
#argomento e mette in output la stringa con i caratteri in ordine invertito, il primo
#andrà per ultimo, l'ultimo per primo. Per complicarvi la vita, per implementare questo
#script potete utilizzare solo assegnamenti a variabili, cicli ed if a piacere, ed i
#comandi echo read e cut. Si suppone che la stringa passata come argomento non
#contenga caratteri e metacaratteri interpretati dalla bash.

if (( $# == 0 )) ; then echo "Insert a string" ; exit 1 ; fi
REVERSE=""
echo $1 | while (( 1 )) ; do
		read -n 1 CAR ;
		if (( $? == 0 )) ; then
			REVERSE=${CAR}${REVERSE}
		else
			echo stringa rovesciata ${REVERSE}
			break
		fi
	done
