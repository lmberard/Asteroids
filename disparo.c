#include "disparo.h"
#include <SDL2/SDL.h>

void disparo_mover(disparo_t *disparo, float dt)
{
	modificar_parametros_disparo(disparo,dt);
}

void disparos_modificar(lista_t *lista, float dt, SDL_Renderer *renderer)
{
	if (lista_es_vacia(lista))
		return;
	iterador_t *iterador_disparos = iterador_crear(lista);
	
	while(!iterador_termino(iterador_disparos))
	{
		disparo_mover(iterador_actual(iterador_disparos)->dato,dt);
		
		disparo_dibujar(iterador_actual(iterador_disparos)->dato,renderer);//Los disparos tienen un pequeño delay no se por qué
		if(tiempo_vida_agotado(iterador_actual(iterador_disparos)->dato))
		{
			eliminar_disparo(iterador_actual(iterador_disparos),lista);
		}
		iterador_siguiente(iterador_disparos);//validar
	}
	//iterador_eliminar(iterador_disparos);//Hay que eliminar el iterador pero esta linea rompe
}

bool disparo_dibujar(disparo_t *disparo, SDL_Renderer *r)//VALIDAR
{
	if((graficador_dibujar(r,NOMBRE_SPRITE_DISPARO, ESCALA_DISPARO , disparo->posicion_x, disparo->posicion_y, disparo->angulo))==false);
		return true;
}

bool tiempo_vida_agotado(disparo_t *disparo)
{
	if(disparo->tiempo_vida <=0)
		return true;
	else return false;
}

void eliminar_disparo(struct nodo *nodo, lista_t *lista)
{
	eliminar_nodo(lista,nodo);
}

void modificar_parametros_disparo(disparo_t *disparo,float dt)
{
	disparo->velocidad_y = computar_velocidad(disparo->velocidad_y,0,dt);
	disparo->velocidad_x = computar_velocidad(disparo->velocidad_x,0,dt);

	disparo->posicion_y = computar_posicion(disparo->posicion_y, disparo->velocidad_y, dt);
	disparo->posicion_x = computar_posicion(disparo->posicion_x, disparo->velocidad_x, dt);

	disparo->tiempo_vida -= dt;
}

void generar_disparo(disparo_t *nuevo_disparo, nave_t nave)
{
	nuevo_disparo->posicion_x = nave.posicion_x;
	nuevo_disparo->posicion_y = nave.posicion_y;
	nuevo_disparo->tiempo_vida = TIEMPO_DISPARO_MAX;

	nuevo_disparo->angulo = nave.angulo;

	nuevo_disparo->velocidad_x = 1000 * cos(nave.angulo);
	nuevo_disparo->velocidad_y = 1000 * sin(nave.angulo);
}


void crear_disparo(lista_t *lista, nave_t nave)
{
	disparo_t *disparo = (disparo_t*)malloc(sizeof(disparo_t)); //VALIDAR, no recuerdo bien como validar fx que devuelven void
	generar_disparo(disparo,nave);
	lista_insertar_final(lista,disparo); //VALIDAR
}
























