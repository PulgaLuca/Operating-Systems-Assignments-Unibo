#!/bin/bash
PREC=""
FILES=`find /usr/include/linux/ -mindepth 2 -name "*.h" -print`
if [[ -z ${FILES} ]] ; then echo "no found files" ; exit 1 ; fi
for FILE in ${FILES} ; do
	if [[ ${PREC} == "" || ${FILE} -nt ${PREC} ]] ; then
		PREC=${FILE}
	fi
done
echo ${PREC}
