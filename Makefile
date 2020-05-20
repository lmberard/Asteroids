CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm -lSDL2
INSTALL_DIR := /usr/sbin

all: tp2

asteroide.o: asteroide.c graficador.h movimientos.h lista.h objetos.h iterador.h asteroide.h
	$(CC) $(CFLAGS) asteroide.c
	
lista.o: lista.c lista.h
	$(CC) $(CFLAGS) lista.c

disparo.o: disparo.c lista.h iterador.h objetos.h disparo.h graficador.h movimientos.h juego.h
	$(CC) $(CFLAGS) disparo.c

iterador.o: iterador.c iterador.h lista.h
	$(CC) $(CFLAGS) iterador.c	

graficador.o: graficador.c graficador.h objetos.h
	$(CC) $(CFLAGS) graficador.c

nave.o: nave.c nave.h movimientos.h
	$(CC) $(CFLAGS) nave.c

caracteres.o: caracteres.c caracteres.h nave.h
	$(CC) $(CFLAGS) caracteres.c

movimientos.o: movimientos.c objetos.h movimientos.h
	$(CC) $(CFLAGS) movimientos.c

vectores.o: vectores.c vectores.h
	$(CC) $(CFLAGS) vectores.c

diccionario.o: diccionario.h diccionario.c
	$(CC) $(CFLAGS) diccionario.c

juego.o: juego.c juego.h disparo.h asteroide.h objetos.h iterador.h lista.h
	$(CC) $(CFLAGS) juego.c

main.o: main.c nave.h movimientos.h diccionario.h vectores.h graficador.h objetos.h disparo.h asteroide.h juego.h
	$(CC) $(CFLAGS) main.c

tp2: main.o nave.o caracteres.o movimientos.o vectores.o diccionario.o graficador.o iterador.o lista.o disparo.o asteroide.o juego.o
	$(CC) $(LFLAGS) $^ -o tp2 -lSDL2 -lm


clean:
	rm *.o

install: tp2
	cp $^ $(INSTALL_DIR)

gdb: tp2
	gdb ./tp2

valgrind: tp2
	valgrind --leak-check=full ./tp2
