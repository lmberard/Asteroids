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
	modificar_parametros_asteroide(asteroide,dt);
	verificar_limites_pantalla_ast(asteroide);
}


void asteroide_modificar(lista_t *lista, float dt, SDL_Renderer *renderer)
{
	if (lista_es_vacia(lista))
		return;

	iterador_t *iterador_asteroide = iterador_crear(lista);
	while(!iterador_termino(iterador_asteroide))
	{
		asteroide_mover(iterador_actual(iterador_asteroide)->dato,dt);
		asteroide_dibujar(iterador_actual(iterador_asteroide)->dato,renderer);//Los asteroide tienen un pequeño delay no se por qué
		//if choco eliminar_asteroide(eliminar asteroide ya esta hecha aca abajo)
		iterador_siguiente(iterador_asteroide);//validar
	}
	iterador_destruir(iterador_asteroide);
}

bool asteroide_dibujar(asteroide_t *asteroide, SDL_Renderer *r)//VALIDAR
{
	if((graficador_dibujar(r,asteroide->nombre, asteroide->radio , asteroide->posicion_x, asteroide->posicion_y, asteroide->angulo))==false);
		return true;
}


void eliminar_asteroide(struct nodo *nodo, lista_t *lista)
{
	eliminar_nodo(lista,nodo);
}

void modificar_parametros_asteroide(asteroide_t *asteroide,float dt)
{
	asteroide->velocidad_y = computar_velocidad(asteroide->velocidad_y,0,dt);
	asteroide->velocidad_x = computar_velocidad(asteroide->velocidad_x,0,dt);

	asteroide->posicion_y = computar_posicion(asteroide->posicion_y, asteroide->velocidad_y, dt);
	asteroide->posicion_x = computar_posicion(asteroide->posicion_x, asteroide->velocidad_x, dt);

}

void generar_asteroide(asteroide_t *nuevo_asteroide)
{
	nuevo_asteroide->posicion_x = generar_aleatorio(0,(float)VENTANA_ANCHO);
	nuevo_asteroide->posicion_y = generar_aleatorio(0,(float)VENTANA_ALTO);
	nuevo_asteroide->radio =  asignar_radio((int)generar_aleatorio(0,3));

	nuevo_asteroide->angulo = generar_aleatorio(0, PI);

	nuevo_asteroide->velocidad_x = generar_aleatorio(nuevo_asteroide->angulo -100,nuevo_asteroide->angulo +100);
	nuevo_asteroide->velocidad_y = generar_aleatorio(nuevo_asteroide->angulo -100,nuevo_asteroide->angulo +100);
	nuevo_asteroide->nombre = asignar_sprite((int) generar_aleatorio(1,CANT_ASTEROIDES_SPRITE));
}


void crear_asteroide(lista_t *lista)
{
	asteroide_t *asteroide = (asteroide_t*)malloc(sizeof(asteroide_t)); //VALIDAR, no recuerdo bien como validar fx que devuelven void
	generar_asteroide(asteroide);
	lista_insertar_final(lista,asteroide); //VALIDAR
}

/*La funcion recibe el valor minimo y maximo entre los cuales devolvera un valor aleatorio de tipo flotante*/
float generar_aleatorio(float minimo, float maximo)
{
	float valor=0;
	float aleatorio;
	aleatorio=(float)rand();
	valor = (float) (( aleatorio / RAND_MAX)* (maximo - minimo) + minimo);
	return valor;
}

char *asignar_sprite(int numero_sprite)//Es muy villero esto? se puede buscar otra implementacion con enum sino
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

float asignar_radio(int nro_radio)//idem
{
	float radio;
	switch(nro_radio)
	{
		case 1:
			radio = RADIO_AST_1;
			break;
		case 2:
			radio = RADIO_AST_2;
			break;
		case 3:
			radio = RADIO_AST_3;
			break;
	}
	return radio;
}
