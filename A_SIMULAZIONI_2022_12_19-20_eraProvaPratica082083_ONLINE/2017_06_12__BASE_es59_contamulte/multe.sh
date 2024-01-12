#!/bin/bash
COUNTER=0
PREC=""
while read NOME COGNOME COSTO GG MM YY ALTRO ; do
	if [[ -z ${NOME} || -z ${COGNOME} || -z ${COSTO} || -z ${GG} || -z ${MM} || -z ${YY} || -n ${ALTRO} ]] ; then
		echo "MISSING DATA"
	else
		if [[ ${PREC} == "" ]] ; then
			COUNTER=1
			PREC=${COSTO}
		fi
		if [[ ${PREC} == ${COSTO} ]] ; then
			(( COUNTER=${COUNTER}+1 ))
		else
			echo "${PREC} ${COUNTER}"
			PREC=${COSTO}
			COUNTER=1
		fi
	fi
done
if [[ ${PREC} != "" ]] ; then
	# nel file c'era qualche riga
	echo "${PREC} ${COUNTER}"
fi

exit 0
