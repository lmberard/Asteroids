#include "juego.h"

//Funcion que devuelve true si el disparo se encuentra en una posicion cercana al asteroide(lo choca)
bool disparo_choca_asteroide(disparo_t *disparo, asteroide_t *asteroide)
{	
	return (distancia_objeto_asteroide(pos_x_disparo(disparo), pos_y_disparo(disparo),asteroide) <= radio_ast(asteroide));
}


void procesar_disparos_asteroides(lista_t *lista_disparo, lista_t *lista_asteroides,float *puntos)
{

	if (lista_es_vacia(lista_disparo) || lista_es_vacia(lista_asteroides))
		return;

	iterador_t *iterador_disparo = iterador_crear(lista_disparo);

	for(nodo_t* nodo_disparo = iterador_actual(iterador_disparo);!iterador_termino(iterador_disparo);iterador_siguiente(iterador_disparo),nodo_disparo = iterador_actual(iterador_disparo))
	{
		iterador_t *iterador_asteroide = iterador_crear(lista_asteroides);
		for(nodo_t* nodo_asteroide = iterador_actual(iterador_asteroide);!iterador_termino(iterador_asteroide);iterador_siguiente(iterador_asteroide),nodo_asteroide = iterador_actual(iterador_asteroide))
		{
			if(disparo_choca_asteroide(nodo_disparo->dato,nodo_asteroide->dato))		
			{	
				partir_asteroide(lista_asteroides,nodo_asteroide->dato);
				asignar_puntaje(nodo_asteroide->dato, puntos);
				liberar_disparo(nodo_disparo->dato);
				iterador_eliminar(iterador_disparo);
				iterador_eliminar(iterador_asteroide);
				break;
			}
		}
		iterador_liberar(iterador_asteroide);
	}
	iterador_liberar(iterador_disparo);
}

void asignar_puntaje(asteroide_t *asteroide,float *puntos)
{
	if(radio_ast(asteroide) == RADIO_AST_3) 
		*puntos += 20;
	else if(radio_ast(asteroide) == RADIO_AST_2)
		*puntos +=50;
	else 
	*puntos +=100;
}

bool hay_vidas_disponibles(int vidas_disponibles)
{
	return vidas_disponibles>0;
}


bool nave_choca_asteroide(lista_t *lista_asteroides,nave_t *nave)
{
	iterador_t *iterador_asteroide = iterador_crear(lista_asteroides); 
	for(nodo_t* nodo_asteroide = iterador_actual(iterador_asteroide);!iterador_termino(iterador_asteroide);iterador_siguiente(iterador_asteroide),nodo_asteroide = iterador_actual(iterador_asteroide))
	{
		if ((distancia_objeto_asteroide(pos_x_nave(nave),pos_y_nave(nave),nodo_asteroide->dato)) <= radio_ast(nodo_asteroide->dato)) 
		{
			partir_asteroide(lista_asteroides,nodo_asteroide->dato);
			iterador_eliminar(iterador_asteroide);
			iterador_liberar(iterador_asteroide);
			return true;
		}	
	}
	iterador_liberar(iterador_asteroide);
	return false;
}

float procesar_mejor_puntaje(float *puntajes, size_t nro_partidas)
{
	selection_sort(puntajes, nro_partidas); 
	return puntajes[0];
}

void reiniciar_partida(lista_t **lista, int *vidas_disponibles, float *puntos)
{
	lista_destruir(*lista, free);
	*vidas_disponibles = CANT_VIDAS_INICIAL;
	*puntos = 0;
	*lista = lista_crear();
	cargar_asteroides(*lista, CANT_ASTEROIDES_INICIAL);				
}

float generar_aleatorio(float minimo, float maximo)
{
	float valor=0;
	float aleatorio;
	aleatorio=(float)rand();
	valor = (float) (( aleatorio / RAND_MAX)* (maximo - minimo) + minimo);
	return valor;
}
