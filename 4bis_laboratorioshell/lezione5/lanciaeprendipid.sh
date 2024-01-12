#!/bin/bash

#Creare altri due script, lanciaekilla.sh e lanciaeprendipid.sh. Lo script
#lanciaeprendipid.sh deve lanciare in background 10 istanze dello script precedente
#puntini.sh ridirigendo l'output di questi script sullo standard error.
#Per ciascuno degli script puntini.sh lanciati, lo script lanciaeprendipid.sh deve
#pttenere il PID del processo lanciato. I 10 PID li deve mandare sullo standard
#output separati da spazi.
#Lo script lanciaekilla.sh invece deve lanciare in modo opportuno lo script
#lanciaeprendipid.sh, deve catturare l'output di questo e visualizzare l'elenco dei PID
#ottenuti.
#Poi deve usare i PID ottenuti per killare uno alla volta i processi puntini.sh lanciati
#da lanciaeprendipid.sh .

for (( NUM=0; ${NUM}<10; NUM=${NUM}+1 )) ; do
	./puntini.sh 30 1>&2 &
	echo "$! "
done
