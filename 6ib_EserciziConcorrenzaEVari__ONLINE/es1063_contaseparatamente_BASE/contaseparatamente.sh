#!/bin/bash
NUM=1
PARI=0
DISPARI=0
if [[ "$#" > 9 ]] ; then echo "too many args" ; fi
while("${NUM}"<"$#") ; do
	ROWS=`wc -l ${!NUM}`
	if (( ${NUM}%2==0 )) ; then
		(( PARI=${PARI}+${ROWS} ))	
	else
		(( PARI=${DISPARI}+${ROWS} ))
	fi
	(( NUM=${NUM}+1 ))
done
echo "PARI: ${PARI}"
echo "DISPARI: ${DISPARI}" 1>&2
