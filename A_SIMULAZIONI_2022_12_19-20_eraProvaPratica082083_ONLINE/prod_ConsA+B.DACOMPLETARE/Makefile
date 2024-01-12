CFLAGS=-ansi -Wpedantic -Wall
LIBRARIES=-lpthread

all: prod_ConsA+B.exe

prod_ConsA+B.exe: prod_ConsA+B.o DBGpthread.o
	gcc -o prod_ConsA+B.exe prod_ConsA+B.o DBGpthread.o ${LIBRARIES}

prod_ConsA+B.o: prod_ConsA+B.c ./DBGpthread.h ./printerror.h
	gcc -c ${CFLAGS} prod_ConsA+B.c

DBGpthread.o: ./DBGpthread.c ./printerror.h
	gcc -c ${CFLAGS} ./DBGpthread.c

.PHONY: clean

clean: 
	rm -f prod_ConsA+B.exe prod_ConsA+B.o DBGpthread.o
