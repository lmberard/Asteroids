#ifndef _OBJETOS_H_
#define _OBJETOS_H_

typedef struct nave{
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo;
	float potencia;
}nave_t;

typedef struct asteroide{
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo;
	float radio;
} asteroide_t;

typedef struct disparo{
	float posicion_x;
	float posicion_y;
	float velocidad_x;
	float velocidad_y;
	float angulo;
	float tiempo_vida;
} disparo_t;

#endif