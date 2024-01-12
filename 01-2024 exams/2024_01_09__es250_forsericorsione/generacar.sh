#!/bin/bash

NUMERO=$(( ${RANDOM} % 3 ))
if   (( $NUMERO==0 )) ; then echo 'a' ;
elif (( $NUMERO==1 )) ; then echo 't' ;
else  echo 'x'; fi

