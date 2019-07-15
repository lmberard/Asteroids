#include "movimientos.h"

float computar_velocidad(float vi, float a, float dt)
{
    return vi + dt*a;
}

float computar_posicion(float pi,float vi,float dt)
{
    return pi + dt*vi;
}


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
