#include "lista.h"
#include <stdlib.h>

nodo_t *nodo_crear(void *d) {
	nodo_t *n = malloc(sizeof(nodo_t));
	if(n == NULL)
		return NULL;

	n->sig = NULL;
	n->dato = d;

	return n;
}

lista_t *lista_crear()
{
	lista_t *l = malloc(sizeof(lista_t));
	if(l == NULL)
		return NULL;

	l->prim = NULL;
	return l;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *d))
{
	nodo_t *n = l->prim;
	while(n != NULL) {
		nodo_t *sig = n->sig;

		if(destruir_dato != NULL)
			destruir_dato(n->dato);

		free(n);

		n = sig;
	}
	free(l);
}

bool lista_es_vacia(const lista_t *l)
{
	return l->prim == NULL;
}

bool lista_insertar_comienzo(lista_t *l, void *d) {
	nodo_t *n = nodo_crear(d);
	if(n == NULL)
		return false;

	n->sig = l->prim;
	l->prim = n;

	return true;
}

bool lista_insertar_final(lista_t *l, void *d)
{
	nodo_t *n = nodo_crear(d);
	if(n == NULL) return false;

	if(l->prim == NULL)
	{
		l->prim = n;
		return true;
	}
	nodo_t *aux = l->prim;
	while(aux->sig != NULL)
		aux = aux->sig;

	aux->sig = n;

	return true;
}


void *lista_extraer_primero(lista_t *l) {
	if(lista_es_vacia(l))
		return NULL;

	struct nodo *n = l->prim;
	void *d = n->dato;

	l->prim = n->sig;
	free(n);

	return d;
}

void destruir_dato(void *dato)
{
	free(dato);
}

bool eliminar_nodo(lista_t *lista, nodo_t *nodo)
{
	nodo_t *act = NULL;
	nodo_t *ant = NULL;
	if(lista_es_vacia(lista))
		return false;
	
	act=lista->prim;

	if(lista->prim==nodo)
	{
		act=act->sig;	
		free(lista->prim->dato);
		free(lista->prim);
		lista->prim=act;
		return true;
	}
	ant=lista->prim;
	act=act->sig;
	
	while (act!=NULL)
	{
		if(nodo==act)
		{
			ant->sig=act->sig;
			free(act->dato);
			free(act);
			return true;
		}	
		ant=ant->sig;
		act=act->sig;
	}
	return false;
}