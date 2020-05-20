#include "disparo.h"
#include <SDL2/SDL.h>

void disparo_mover(disparo_t *disparo, float dt)
{
	modificar_parametros_disparo(disparo,dt);
}

void lista_disparos_modificar(lista_t **lista, float dt, SDL_Renderer *renderer)
{
	if (lista_es_vacia(*lista))
		return;
	
	iterador_t *iterador_disparos = iterador_crear(*lista);
	
	while(!iterador_termino(iterador_disparos))
	{
		disparo_mover(iterador_actual(iterador_disparos)->dato,dt);
		disparo_dibujar(iterador_actual(iterador_disparos)->dato,renderer);
		
		iterador_siguiente(iterador_disparos);
	}
	iterador_liberar(iterador_disparos);
}

void liberar_disparo(disparo_t *disparo)
{
	free(disparo);
}

bool disparo_dibujar(disparo_t *disparo, SDL_Renderer *r)
{
	return !graficador_dibujar(r,NOMBRE_SPRITE_DISPARO, ESCALA_DISPARO , disparo->posicion_x, disparo->posicion_y, disparo->angulo);
}

bool tiempo_vida_agotado(disparo_t *disparo)
{
	if(disparo->tiempo_vida <=0)
		return true;
	else return false;
}

void eliminar_disparo_agotado(lista_t *lista)
{
	destruir_dato(lista_extraer_primero(lista));
}

void modificar_parametros_disparo(disparo_t *disparo,float dt)
{
	disparo->posicion_y = computar_posicion(disparo->posicion_y, disparo->velocidad_y, dt);
	disparo->posicion_x = computar_posicion(disparo->posicion_x, disparo->velocidad_x, dt);
	disparo->tiempo_vida -= dt;
}

void cargar_parametros_disparo(disparo_t *nuevo_disparo, nave_t *nave)
{
	nuevo_disparo->posicion_x = pos_x_nave(nave);
	nuevo_disparo->posicion_y = pos_y_nave(nave);
	nuevo_disparo->tiempo_vida = TIEMPO_DISPARO_MAX;

	nuevo_disparo->angulo = angulo_nave(nave);

	nuevo_disparo->velocidad_x = VELOCIDAD_DISPARO * cos(angulo_nave(nave));
	nuevo_disparo->velocidad_y = VELOCIDAD_DISPARO * sin(angulo_nave(nave));
}


disparo_t* disparo_crear()
{
	disparo_t *disparo; 
	if((disparo = (disparo_t*)malloc(sizeof(disparo_t)))==NULL)
		return NULL;
	else return disparo;
}

float pos_x_disparo(disparo_t *disparo)
{
	return disparo->posicion_x;
}

float pos_y_disparo(disparo_t *disparo)
{
	return disparo->posicion_y;
}








