CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm -lSDL2
INSTALL_DIR := /usr/sbin

all: tp2

lista.o: lista.h
	$(CC) $(CFLAGS) lista.c

disparo.o: lista.h iterador.h objetos.h disparo.h
	$(CC) $(CFLAGS) disparo.c

iterador.o: iterador.h lista.h
	$(CC) $(CFLAGS) iterador.c	

graficador.o: graficador.h config.h objetos.h
	$(CC) $(CFLAGS) graficador.c

naves.o: naves.c naves.h movimientos.h
	$(CC) $(CFLAGS) naves.c

caracteres.o: caracteres.c caracteres.h naves.h
	$(CC) $(CFLAGS) caracteres.c

movimientos.o: movimientos.c objetos.h movimientos.h
	$(CC) $(CFLAGS) movimientos.c

vectores.o: vectores.c vectores.h
	$(CC) $(CFLAGS) vectores.c

diccionario.o: diccionario.h diccionario.c
	$(CC) $(CFLAGS) diccionario.c

renderizar.o: renderizar.c renderizar.h diccionario.h
	$(CC) $(CFLAGS) renderizar.c


main.o: main.c config.h nave.h movimientos.h diccionario.h vectores.h renderizar.h graficador.h objetos.h disparo.h
	$(CC) $(CFLAGS) main.c

tp2: main.o nave.o caracteres.o movimientos.o vectores.o diccionario.o renderizar.o graficador.o iterador.o lista.o disparo.o
	$(CC) $(LFLAGS) $^ -o tp2 -lSDL2 -lm

clean:
	rm *.o

install: tp2
	cp $^ $(INSTALL_DIR)

valgrind: tp1
	valgrind --leak-check=full ./tp1
