#!/bin/bash

while read MATR EMAIL; do
	if [[ -z ${MATR} || -z ${EMAIL} ]] ; then echo "args needed" ; exit 2 ; fi
	./cercastudente.sh ${EMAIL} ${MATR}
done < ./email.txt
