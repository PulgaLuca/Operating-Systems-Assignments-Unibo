#!/bin/bash

#scrivere una riga di comando che mette sullo standard output le righe che stanno
#tra la 3° e la 5° posizione nel file /usr/include/stdio.h

PATH=/usr/include/stdio.h
`head -n 3 ${PATH} | tail -n 3`
