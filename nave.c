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

/*Funcion que asigna a los parametros de la nave sus valores iniciales*/
void inicializar_valores(nave_t *nave)
{
	//fprintf(stderr, "entra a inicializar_valores\n");
   	nave->potencia = (float) NAVE_POTENCIA_INICIAL;
	nave->posicion_x = (float) NAVE_X_INICIAL;
	nave->posicion_y = (float) NAVE_Y_INICIAL;
	nave->velocidad_x = (float) NAVE_VX_INICIAL;
	nave->velocidad_y = (float) NAVE_VY_INICIAL;
	nave->angulo = (float) NAVE_ANGULO_INICIAL;
	///fprintf(stderr, "termina de inicializar_valores\n");
}
			
void computar_pot(nave_t *nave)
{
	nave->potencia -= nave->potencia*0.1;// en cada dt, se disminuye un 10%

	if(nave->potencia <=0)
		nave->potencia=NAVE_POTENCIA_INICIAL;
	if (nave->potencia >= NAVE_MAX_POTENCIA)
		nave->potencia = NAVE_MAX_POTENCIA;
}

void nave_mover(nave_t *nave, float dt)
{
	computar_pot(nave);
	modificar_parametros_nave(nave,dt);
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
	nave->velocidad_y = computar_velocidad (nave->velocidad_y,nave->potencia*sin(nave->angulo),dt);
	nave->velocidad_x = computar_velocidad(nave->velocidad_x, nave->potencia*cos(nave->angulo),dt);
	
	//POR CADA DT LA VELOCIDAD DISMINUYE UN 1%
	nave->velocidad_y -= nave->velocidad_y *0.01;
	nave->velocidad_x -= nave->velocidad_x *0.01;

	nave->posicion_y = computar_posicion(nave->posicion_y, nave->velocidad_y, dt);
	nave->posicion_x = computar_posicion(nave->posicion_x, nave->velocidad_x, dt);
}
				
