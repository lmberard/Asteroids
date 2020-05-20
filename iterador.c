#include "iterador.h"
#include "lista.h"


iterador_t *iterador_crear(lista_t *l)
{
	iterador_t *iterador;

	if((iterador= malloc(sizeof(iterador_t)))==NULL)
		return NULL;

	if(lista_es_vacia(l)==true)
	{
		iterador->nodo_anterior = NULL;
		iterador->nodo_iterador = NULL;
		return iterador;
	}
	iterador->lista_iterador = l;
	iterador->nodo_anterior = NULL;
	iterador->nodo_iterador = l->prim;

	return iterador;
}


void iterador_liberar(iterador_t *li)
{
	free(li);
}

nodo_t *iterador_actual(const iterador_t *li)
{
	if(li->nodo_iterador==NULL)
		return NULL;

	return li->nodo_iterador;
}

bool iterador_siguiente(iterador_t *li)
{
	if(li->nodo_iterador==NULL)
		return false;
	
	li->nodo_anterior = li->nodo_iterador;
	li->nodo_iterador = li->nodo_iterador->sig;
	return true;
}

bool iterador_termino(const iterador_t *li)
{
	if(li->nodo_iterador == NULL)
		return true;
	return false;
}

void iterador_eliminar(iterador_t *li)
{
	if(li->nodo_iterador == NULL)
		return;
	
	if(li->nodo_anterior == NULL) 
	{
		nodo_t *n = li->lista_iterador->prim;
		li->lista_iterador->prim = n->sig;
		free(n);
		return;
	}
	else
	{
		li->nodo_anterior->sig = li->nodo_iterador->sig;
		nodo_t *aux = li->nodo_iterador->sig;
		free(li->nodo_iterador);
		li->nodo_iterador = aux;
	}
}