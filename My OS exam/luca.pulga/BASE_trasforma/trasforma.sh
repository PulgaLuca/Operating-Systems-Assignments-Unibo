#!/bin/bash

var1=A
var2=B

# VIC: completare a partire da qui.
while read P1 P2 P3 ; do
	if [[ ${P1}  == "VISUALIZZA" ]] ; then
		if [[ ${P2} == "var1" ]] ; then
			echo "${var1}"
		else
			echo "${var2}"
		fi
	else
		if [[ ${P2} == "var1" ]] ; then
			var1=${P3}
		else
			var2=${P3}
		fi
	fi
done
exit 0
