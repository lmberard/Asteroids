#include "asteroide.h"
#include <SDL2/SDL.h>

void verificar_limites_pantalla_ast(asteroide_t *asteroide)
{
	if(asteroide->posicion_x >= VENTANA_ANCHO)
		asteroide->posicion_x = 10;
				
	if(asteroide->posicion_x <= 0)
		asteroide->posicion_x = VENTANA_ANCHO-10;

	if(asteroide->posicion_y >= VENTANA_ALTO)
		asteroide->posicion_y = 10;

	if(asteroide->posicion_y <=0)
		asteroide->posicion_y = VENTANA_ALTO -10;
}

void asteroide_mover(asteroide_t *asteroide, float dt)
{
	asteroide->velocidad_y = computar_velocidad(asteroide->velocidad_y,0,dt);
	asteroide->velocidad_x = computar_velocidad(asteroide->velocidad_x,0,dt);

	asteroide->posicion_y = computar_posicion(asteroide->posicion_y, asteroide->velocidad_y, dt);
	asteroide->posicion_x = computar_posicion(asteroide->posicion_x, asteroide->velocidad_x, dt);

	verificar_limites_pantalla_ast(asteroide);
}


void lista_asteroides_mover_dibujar(lista_t *lista, float dt, SDL_Renderer *renderer)
{
	if (lista_es_vacia(lista))
		return;
	iterador_t *iterador_asteroide = iterador_crear(lista);

	while(!iterador_termino(iterador_asteroide))
	{	
		asteroide_mover(iterador_actual(iterador_asteroide)->dato,dt);

		if(!asteroide_dibujar(iterador_actual(iterador_asteroide)->dato,renderer))
			break;

		if(!iterador_siguiente(iterador_asteroide))
			break;

	}
	iterador_liberar(iterador_asteroide);
}

bool asteroide_dibujar(asteroide_t *asteroide, SDL_Renderer *r)
{
	return graficador_dibujar(r,asteroide->nombre, asteroide->radio , asteroide->posicion_x, asteroide->posicion_y, asteroide->angulo);
}


void cargar_parametros_asteroide(asteroide_t *nuevo_asteroide, float posicion_x, float posicion_y)
{
	nuevo_asteroide->posicion_x = posicion_x;
	nuevo_asteroide->posicion_y = posicion_y;

	nuevo_asteroide->angulo = generar_aleatorio(0, PI);

	nuevo_asteroide->velocidad_x = generar_aleatorio(nuevo_asteroide->angulo -100,nuevo_asteroide->angulo +100);
	nuevo_asteroide->velocidad_y = generar_aleatorio(nuevo_asteroide->angulo -100,nuevo_asteroide->angulo +100);

	nuevo_asteroide->nombre = asignar_sprite((int)generar_aleatorio(1,CANT_ASTEROIDES_SPRITE));
}

void cargar_radio_asteroide(asteroide_t *asteroide , int radio_ast)
{
	asteroide->radio = radio_ast;
}

asteroide_t *asteroide_crear()
{
	asteroide_t *asteroide = (asteroide_t*)malloc(sizeof(asteroide_t));
	if (asteroide == NULL)
		return NULL;
	else return asteroide;
}

void generar_asteroides(lista_t *lista, size_t cant_asteroides, int radio_ast, float posicion_x, float posicion_y)
{
	for(size_t i = 0; i < cant_asteroides;i++)
	{
		asteroide_t *asteroide = asteroide_crear();
		cargar_parametros_asteroide(asteroide,posicion_x,posicion_y);
		cargar_radio_asteroide(asteroide,radio_ast);
		lista_insertar_final(lista,asteroide); 
	}	
}

char *asignar_sprite(int numero_sprite)
{
	char* nombre = NULL;
	switch(numero_sprite)
	{
		case 1:
			nombre = NOMBRE_SPRITE_AST_1;
			break;
		case 2:
			nombre = NOMBRE_SPRITE_AST_2;
			break;
		case 3:
			nombre = NOMBRE_SPRITE_AST_3;
			break;
		case 4:
			nombre = NOMBRE_SPRITE_AST_4;
			break;
	}
	return nombre;
}
void cargar_asteroides(lista_t *lista, int cant_asteroides)
{
	for(size_t i = 0; i < cant_asteroides; i++)
	{
		float posicion_x = generar_aleatorio(0,(float)VENTANA_ANCHO);
		float posicion_y = generar_aleatorio(0,(float)VENTANA_ALTO);
		generar_asteroides(lista,1, RADIO_AST_3,posicion_x,posicion_y);
	}
}	



void partir_asteroide(lista_t *lista, asteroide_t *asteroide)
{
	if(asteroide->radio == RADIO_AST_1)
	{
		return;
	}
	if(asteroide->radio == RADIO_AST_2)
	{
		generar_asteroides(lista,AUMENTO_CANT_ASTEROIDES,RADIO_AST_1,asteroide->posicion_x,asteroide->posicion_y);
		liberar_asteroide(asteroide);
		return;
	}
	if(asteroide->radio == RADIO_AST_3)
	{
		generar_asteroides(lista,AUMENTO_CANT_ASTEROIDES,RADIO_AST_2,asteroide->posicion_x,asteroide->posicion_y);
		liberar_asteroide(asteroide);
		return;
	}
}
void liberar_asteroide(asteroide_t *asteroide)
{
	free(asteroide);
}


float radio_ast(asteroide_t *asteroide)
{
	return asteroide->radio;
}


float distancia_objeto_asteroide(float posicion_x, float posicion_y, asteroide_t *asteroide)
{
	float distancia_x = (asteroide->posicion_x - posicion_x) * (asteroide->posicion_x - posicion_x );
	float distancia_y = (asteroide->posicion_y - posicion_y) * (asteroide->posicion_y - posicion_y );
	return sqrt(distancia_x + distancia_y);
}
 