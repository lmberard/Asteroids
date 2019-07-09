#include "nave.h"
#include "movimientos.h"

void nave_mover(nave_t *nave, float dt)
{
	modificar_parametros_nave(nave,dt);
	computar_pot(nave);
	verificar_limites_pantalla(nave);
}

bool nave_dibujar(nave_t *nave, SDL_Renderer *r)
{
	//fprintf(stderr, "entro a navedibujar\n");
	if((graficador_dibujar(r, NOMBRE_SPRITE_NAVE, ESCALA_NAVE, nave->posicion_x, nave->posicion_y, nave->angulo))==false);
	if((graficador_dibujar(r, NOMBRE_SPRITE_CHORRO, ESCALA_NAVE, nave->posicion_x, nave->posicion_y, nave->angulo))==false);
/*EL chorro hay que modificarlo con la potencia,eso está sin hacer*/
	return true;
}
void modificar_parametros_nave(nave_t *nave,float dt)
{
	nave->velocidad_y = computar_velocidad (nave->velocidad_y,nave->potencia*cos(nave->angulo),dt);
	nave->velocidad_x = computar_velocidad(nave->velocidad_x, nave->potencia*sin(-nave->angulo),dt);

	nave->posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);
	nave->posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
}
				
