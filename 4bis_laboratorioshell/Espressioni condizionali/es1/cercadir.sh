#!/bin/bash

# Sono directory -d
# -r permessi in lettura effective user
# -nt per newest <file> / -ot per oldest <file>
# se la condizione del ciclo fosse:
#	ls /usr/include/*  --> esegue ls sulle dir in /usr/include e non anche sulle subdir
#	`ls /usr/include/* --> va ricorsivamente ad eseguire ls e mostra i file correnti in ogni subdir
#	ls -d /usr/include/* -->  come nel primo caso
IT = 0;
for th in `ls -d /usr/include/*` ; do
	if [[ -d ${th} && -r ${th} &&  ${th} -nt /usr/include/stdio.h ]];
		echo "${th}";
	then
		echo "/usr/include/${th}";
	fi
	(( IT=${IT}+1 ));
done
echo "IT: ${IT}";
