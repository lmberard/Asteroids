#include "lista.h"
#include <stdlib.h>


struct nodo *nodo_crear(void *d) {
	struct nodo *n = malloc(sizeof(struct nodo));
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
	struct nodo *n = l->prim;
	while(n != NULL) {
		struct nodo *sig = n->sig;

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
	struct nodo *n = nodo_crear(d);
	if(n == NULL)
		return false;

	n->sig = l->prim;
	l->prim = n;

	return true;
}

bool lista_insertar_final(lista_t *l, void *d)
{
	struct nodo *n = nodo_crear(d);
	if(n == NULL) return false;

	// Si estÃ¡ vacÃ­a inserto al principio:
	if(l->prim == NULL)
	{
		l->prim = n;
		return true;
	}

	// La lista no estaba vacÃ­a:
	struct nodo *aux = l->prim;
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

void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b)) {

	struct nodo *n = l->prim;
	while(n != NULL) {
		if(cmp(n->dato, d) == 0)
			return n->dato;

		n = n->sig;
	}

	return NULL;
}

void lista_mapear(lista_t *l, void *(*f)(void *dato))
{
	struct	nodo *nodo_aux = l->prim;

	while(nodo_aux!=NULL)
	{
		nodo_aux->dato = f(nodo_aux->dato);
		nodo_aux = nodo_aux->sig;
	}
}


bool eliminar_nodo(lista_t *lista, struct nodo *nodo)
{
	struct nodo *act = NULL;
	struct nodo *ant = NULL;
	if(lista_es_vacia(lista))
		return false;

	act=lista->prim;
	ant=lista->prim;
	act=act->sig;

	while (act!=NULL)
	{
		if(nodo==act)//villero, encontrar forma alternativa de hacer
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

