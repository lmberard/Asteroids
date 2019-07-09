#include "iterador.h"
#include "lista.h"


iterador_t *iterador_crear(lista_t *l)
{
	iterador_t *iterador;

	if((iterador= malloc(sizeof(iterador_t)))==NULL)//pido memoria para un iterador
		return NULL;

	//iterador->nodo_iterador = NULL;//primer nodo a null, lista vacia

	iterador->nodo_anterior = NULL;
	iterador->nodo_iterador = l->prim;

	return iterador;
}


void iterador_destruir(iterador_t *li)
{
	free(li);
}


struct nodo *iterador_actual(const iterador_t *li)
{
	if(li->nodo_iterador==NULL)
		return NULL;

	return li->nodo_iterador;
}

bool iterador_siguiente(iterador_t *li)
{
	if(li->nodo_iterador->sig==NULL)
		return false;
	
	li->nodo_anterior = li->nodo_iterador;
	li->nodo_iterador = li->nodo_iterador->sig;
	return true;

}

bool iterador_termino(const iterador_t *li)
{
	if(li->nodo_iterador->sig == NULL)
		return true;

	return false;
}

void *iterador_eliminar(iterador_t *li) {
	
	if(li->nodo_iterador == NULL)
		return NULL;
	
	if(li->nodo_anterior == NULL) //el elemento a eliminar es el primero de la lista
	{
		free(li->nodo_iterador);
		li->nodo_iterador = li->nodo_iterador->sig;
		//return lista_extraer_primero(li->l);
	}

	void *d = li->nodo_iterador->dato;

	li->nodo_anterior->sig = li->nodo_iterador->sig;
	struct nodo *aux = li->nodo_iterador->sig;
	free(li->nodo_iterador);
	li->nodo_iterador = aux;

	return d;
}


/*void *iterador_eliminar(iterador_t *li)
{

   //while(l->prim && l->prim->dato == estructura) 
	  struct nodo *anterior = l->prim;

      li->nodo_iterador = li->nodo_iterador->sig;
      
      free(l->prim);
      
      l->prim = aux;
   }

   // Borro del resto:
   struct nodo *ant = l->prim;
   while(ant->sig) 
   {
      struct nodo *actual = ant->sig;
      if(actual->dato == estructura) 
      {
         ant->sig = actual->sig;
         free(actual);
      }
      else
          ant = actual;
   }
	if((iterador_siguiente(iterador))==false)
			break;

	return li->nodo_iterador->dato;
}*/
/*
bool eliminar_nodo_actual (lista_t * l, nodo_t *eliminar, bool (*comparar)(void * dato1, void *dato2)){
	nodo_t *actual, *anterior;
	actual=l->prim;
	
	if(comparar(l->prim,eliminar)){
		actual=actual->sig;
		//free(l->prim->dato);
		free(l->prim);
		l->prim=actual;
		return true;
	}

	anterior=l->prim;
	actual=actual->sig;

	while (actual!=NULL){
		if(comparar(actual,eliminar)){
			anterior->sig=actual->sig;
			//free(actual->dato); 
			//esto es por si el dato tambien pide memoria. Si es estatico no hay que ponerlo, chequear cuando carguemos las listas. 
			free(actual);
			return true;
		}
		anterior=anterior->sig;
		actual=actual->sig;
	}
	return false;
}*/

/*
bool comparar_punteros(void *a,void *b){
	return (a==b);
}*/

/* FUNCIONES AUXILIARES QUE HICE PARA PROBAR LA ANTERIOR 
LAS DEJO POR SI LAS DUDAS
nodo_t* crear_nodo(){
	nodo_t * n;
	n=malloc(sizeof(nodo_t));
	if(n==NULL){
		puts("no se asigno memoria a n");
	}
	return n;
}
void imprimir_lista(lista_t*l){
	nodo_t*iterador;
	iterador=l->prim;
	while(iterador!=NULL){
		printf("%i\t",*(int*)iterador->dato);
		iterador=iterador->sig;
	}
}
*/
