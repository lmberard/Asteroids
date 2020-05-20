#ifndef _ITERADOR_H_
#define _ITERADOR_H_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	nodo_t *nodo_iterador;
	nodo_t *nodo_anterior;
	lista_t *lista_iterador;
}iterador_t;

iterador_t *iterador_crear(lista_t *l);
nodo_t *iterador_actual(const iterador_t *li);
bool iterador_siguiente(iterador_t *li);
bool iterador_termino(const iterador_t *li);
void iterador_eliminar(iterador_t *li);
void iterador_liberar(iterador_t *li);
#endif
