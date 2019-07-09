#include "movimientos.h"
/*Funcion que computa el valor de velocidad instantanea*/
float computar_velocidad(float vi, float a, float dt)
{
    return vi + dt*a;
}
/*Funcion que computa el valor de la posicion instantanea*/
float computar_posicion(float pi,float vi,float dt)
{
    return pi + dt*vi;
}
/*Funcion que recibe una matriz de 2 columnas y n elementos y traslada estos en un valor x e y respectivamente*/

void trasladar_vector(float **v, size_t n, float dx, float dy)
{
	for (size_t i = 0; i < n; i++) 
	{
		v[i][0] += dx;
		v[i][1] += dy;
	}
}

void rotar_vector(float **v, size_t n, float angulo)
{
	size_t i;
	float x_rotado;
	float y_rotado;
	float coseno = cos(angulo);
	float seno = sin(angulo);

	for(i=0;i<n;i++)
	{
		x_rotado = v[i][0] * coseno - v[i][1] * seno;
		y_rotado = v[i][0] * seno + v[i][1] * coseno;
		v[i][0] = x_rotado;
		v[i][1] = y_rotado;
	}
}


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

//void inicializar_variables(float posicion_x, float posicion_y, float velocidad_x, float velocidad_y, float angulo, float x_anterior){}
void inicializar_valores(nave_t *nave)
{	
	nave->potencia = (float) NAVE_POTENCIA_INICIAL;
	nave->posicion_x = (float) NAVE_X_INICIAL;
	nave->posicion_y = (float) NAVE_Y_INICIAL;
	nave->velocidad_x = (float) NAVE_VX_INICIAL;
	nave->velocidad_y = (float) NAVE_VY_INICIAL;
	nave->angulo = (float) NAVE_ANGULO_INICIAL;
}


void computar_pot(nave_t *nave)//Esta funcion está medio mal medio bien, hay que pulirla tal que la potencia sea solo un IMPULSO
{
	//nave->potencia -= nave->potencia * 0.1;
	nave->potencia = nave->potencia * 1000;
	if(nave->potencia <=0)
		nave->potencia=NAVE_POTENCIA_INICIAL;
	if (nave->potencia >= NAVE_MAX_POTENCIA)
		nave->potencia = NAVE_MAX_POTENCIA;
}
