#include "nave.h"
#include "movimientos.h"

void verificar_limites_pantalla(nave_t *nave)
{
	if(nave->posicion_x >= VENTANA_ANCHO)
		nave->posicion_x = 10;
				
	if(nave->posicion_x <= 0)
		nave->posicion_x = VENTANA_ANCHO-10;

	if(nave->posicion_y >= VENTANA_ALTO)
		nave->posicion_y = 10;

	if(nave->posicion_y <=0)
		nave->posicion_y = VENTANA_ALTO -10;
}


void inicializar_valores(nave_t *nave)
{
   	nave->potencia = (float) NAVE_POTENCIA_INICIAL;
	nave->posicion_x = (float) NAVE_X_INICIAL;
	nave->posicion_y = (float) NAVE_Y_INICIAL;
	nave->velocidad_x = (float) NAVE_VX_INICIAL;
	nave->velocidad_y = (float) NAVE_VY_INICIAL;
	nave->angulo = (float) NAVE_ANGULO_INICIAL;
}
			
void computar_pot(nave_t *nave)
{
	nave->potencia -= nave->potencia*REDUCCION_POTENCIA;

	if(nave->potencia <=0)
		nave->potencia=NAVE_POTENCIA_INICIAL;
	if (nave->potencia >= NAVE_MAX_POTENCIA)
		nave->potencia = NAVE_MAX_POTENCIA;
}

nave_t* nave_crear()
{
	nave_t* nave =(nave_t*) malloc(sizeof(nave_t));
	if(nave==NULL)
		return NULL;
	else return nave;
}

void nave_mover(nave_t *nave, float dt)
{
	computar_pot(nave);
	modificar_parametros_nave(nave,dt);
	verificar_limites_pantalla(nave);
}

bool nave_dibujar(nave_t *nave, SDL_Renderer *r)
{
	if((graficador_dibujar(r, NOMBRE_SPRITE_NAVE, ESCALA_NAVE, nave->posicion_x, nave->posicion_y, nave->angulo))==false);
	return true;
}

bool chorro_dibujar(nave_t *nave, SDL_Renderer *r)
{
	if((graficador_dibujar(r, NOMBRE_SPRITE_CHORRO, ESCALA_NAVE, pos_x_nave(nave),pos_y_nave(nave),angulo_nave(nave)))==false);
	return true;
}
void modificar_parametros_nave(nave_t *nave,float dt)
{
	nave->velocidad_y = computar_velocidad (nave->velocidad_y,nave->potencia*sin(nave->angulo),dt);
	nave->velocidad_x = computar_velocidad(nave->velocidad_x, nave->potencia*cos(nave->angulo),dt);
	
	nave->velocidad_y -= nave->velocidad_y *REDUCCION_VELOCIDAD;
	nave->velocidad_x -= nave->velocidad_x *REDUCCION_VELOCIDAD;

	nave->posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);
	nave->posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
}
				

void reiniciar_nave(nave_t *nave, float angulo)
{
	nave->posicion_x = VENTANA_ANCHO/2;
	nave->posicion_y = VENTANA_ALTO/2;
	nave->velocidad_x= NAVE_VX_INICIAL;
	nave->velocidad_y = NAVE_VY_INICIAL;
	nave->angulo = angulo;
	nave->potencia = 0;

}

float pos_x_nave(nave_t* nave)
{
	return nave->posicion_x;
}


float pos_y_nave(nave_t* nave)
{
	return nave->posicion_y;
}


float angulo_nave(nave_t* nave)
{
	return nave->angulo;
}

void nave_liberar(nave_t *nave)
{
	free(nave);
	return;
}