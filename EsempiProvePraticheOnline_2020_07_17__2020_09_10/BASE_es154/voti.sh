### Nei commenti che seguono vedete dei suggerimenti sull'algoritmo da
### seguire per produrre l'output corretto.
###

# I voti della seconda prova li devo mettere tutti nello standard output
cat esame2.txt

# Poi devo mettere nello standard output i voti della prima prova
# ottenuti dagli studenti che non hanno un voto nella seconda prova
while read MAT GRADE ; do 
	OUT=`grep ${MAT} esame2.txt`
	if [[ -z ${OUT} ]] ; then
		echo "${MAT} ${GRADE}"
	fi
done < esame1.txt
