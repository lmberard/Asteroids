

#include "juego.h"


bool nave_choco_con_asteroide(nave_t *nave, asteroide_t *asteroide)
{
	/*
	return (nave->posicion_x == asteroide->posicion_x && nave->posicion_y ==asteroide->posicion_y);
	esto esta mal porque que coincidan ubicacion exacta es re imposible, nunca chocaria. Asique me fijo aprox una distancia razonable
	*/
	
	float distancia_x = fabs(nave->posicion_x - asteroide->posicion_x);
	float distancia_y = fabs(nave->posicion_y - asteroide->posicion_y);

	return (distancia_x <= asteroide->radio && distancia_y <= asteroide->radio);//menor o igual que el radio del asteroide?
}

//Esta funcion compara la posicion de la nave con la de cada asteroide, devuelve true si choca con alguno.
bool colisiono_nave_asteroides(nave_t *nave, lista_t *lista_asteroides)
{
	//si la lista de asteroides esta vacia chauu
	if (lista_es_vacia(lista_asteroides))
		return false;

	//creo un iterador para la lista de asteroides
	iterador_t *iterador_asteroide = iterador_crear(lista_asteroides);

	//itero la lista de asteroides:
	while(!iterador_termino(iterador_asteroide))
	{
		//si ese asteroide no choco con la nave, sigo y si choco devuelvo true
		if(!nave_choco_con_asteroide(nave, iterador_actual(iterador_asteroide)))
			iterador_siguiente(iterador_asteroide);
		else 
		{
			//tengo que destruir ese asteroide y crear dos nuevos
			iterador_destruir(iterador_asteroide);
			return true;
		}
	}
	//si no choco con ningun asteroide:
	iterador_destruir(iterador_asteroide);
	return false;
}

/*despues en el main tendria que poner:

if(colisiono_nave_asteroide(&nave, lista_asteroides)
{
	vidas_disponibles --;
	if(hay_vidas_disponibles(vidas_disponibles))
		comenzar_nueva_vida(&nave, lista_asteroides);
	else
		comenzar_nueva_partida();
}
*/
/*
void comenzar_nueva_vida(nave_t *nave, lista_t *lista_asteroides, SDL_Renderer *renderer)
{
		//destruir nave

		Para crear la nueva nave se esperará en principio 1 s, pero si al cumplirse el segundo
		hubiera un asteroide que colisione con el sitio de aparición de la nave se esperará una décima de
		segundo más y se continuarán sumando décimas hasta que la ubicación de la nave sea segura.
				
		inicializar_valores(nave);
		dibujar_vidas(nave, renderer, vidas_disponibles); //esto es un bool..
}

void comenzar_nueva_partida()
{
	//dibujar_game_over(puntos, mejor_puntaje)
	//en realidad lo del mejor puntaje tendria que ser un vector dinamico donde me vaya guardando los puntajes

	//mientras que aparece el cartelito de game over con los puntajes, si aprieto espacio tendria que poner jugar una nueva partida. 

	//vuelvo a tener 4 vidas, tengo que inicializar la nave y crear los asteroides sobre los ejes
}
*/
///////////////////////////////////////////////////////////////////////////////


//Funcion que devuelve true si el disparo se encuentra en una posicion cercana al asteroide(lo choca)
bool disparo_choca_al_asteroide(disparo_t *disparo, asteroide_t *asteroide)
{
	float distancia_x = fabs(disparo->posicion_x - asteroide->posicion_x);
	float distancia_y = fabs(disparo->posicion_y - asteroide->posicion_y);

	return (distancia_x <= asteroide->radio && distancia_y <= asteroide->radio);
}

 
void analizar_disparos(lista_t *lista_disparo, lista_t *lista_asteroides, float *puntos)
{
	//si alguna de las listas esta vacia chauu;
	if (lista_es_vacia(lista_disparo) || lista_es_vacia(lista_asteroides))
		return;

	//creo iteradores para ambas listas
	iterador_t *iterador_asteroide = iterador_crear(lista_asteroides);
	iterador_t *iterador_disparo = iterador_crear(lista_disparo);

	//itero la lista de disparos
	while(!iterador_termino(iterador_disparo))
	{
		//por cada disparo verifico si choca contra alguno de los asteroides(como un for adentro de un for)
		while(!iterador_termino(iterador_asteroide))
		{
			if(disparo_choca_al_asteroide(iterador_actual(iterador_disparo), iterador_actual(iterador_asteroide)))
			{
				//borro el disparo
				//borro ese asteroide y creo dos de radio mas chico
				asignar_puntaje(iterador_actual(iterador_asteroide), puntos);
			}
		iterador_siguiente(iterador_asteroide);
		}
	}
	iterador_destruir(iterador_asteroide);
	iterador_destruir(iterador_disparo);
}

//Asigna un puntaje segun el tipo de asteroide que se haya disparado.
void asignar_puntaje(asteroide_t *asteroide, float *puntos)
{
	//La destrucción de un asteroide grande entrega 20 puntos, la de uno mediano 50 y la de uno pequeño 100 puntos.
	if(asteroide->radio == RADIO_AST_3) 
		*puntos += 20;
	else if(asteroide->radio == RADIO_AST_2)
		*puntos +=50;
		else 
			*puntos +=100;
}

/*
Si no quedaran más asteroides en la pantalla se generarán nuevos asteroides con las caracteristicas del principio.
Cada vez que no queden asteroides se crearán 2 asteroides más que la vez anterior.
#define AUMENTO_CANT_ASTEROIDES 2
*/
void generar_nuevos_asteroides(lista_t *lista_asteroides, int cant_asteroides)
{
	if(lista_es_vacia(lista_asteroides))
	{
		cant_asteroides += AUMENTO_CANT_ASTEROIDES;
		for(int i = 0; i <= cant_asteroides; i++)
			crear_asteroide(lista_asteroides);
	}
}
