#!/bin/bash
OLDIFS=${IFS}
IFS=$'\t\n'
for name in `ls -1 aa*` ; do echo ${name} ; done
IFS=${OLDIFS}
