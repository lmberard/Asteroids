#ifndef _ITERADOR_H_
#define _ITERADOR_H_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	struct nodo *nodo_iterador;
	struct nodo *nodo_anterior;
}iterador_t;

iterador_t *iterador_crear(lista_t *l);
struct nodo *iterador_actual(const iterador_t *li);
bool iterador_siguiente(iterador_t *li);
bool iterador_termino(const iterador_t *li);
void *iterador_eliminar(iterador_t *li);
void iterador_destruir(iterador_t *li);

#endif
