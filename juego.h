#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "iterador.h"
#include "math.h"
#include "vectores.h"
#include "disparo.h"
#include "asteroide.h"
#include "nave.h"


#define PI 3.14159265358979323846

#define JUEGO_FPS 100
#define CANT_MAX_JUEGOS 10
#define CANT_VIDAS_INICIAL 4


bool nave_choca_asteroide(lista_t *lista_asteroides,nave_t *nave);

float distancia_objeto_asteroide(float posicion_x, float posicion_y, asteroide_t *asteroide);

//Funcion que devuelve true si el disparo se encuentra en una posicion cercana a un solo asteroide(lo choca)
bool disparo_choca_asteroide(disparo_t *disparo, asteroide_t *asteroide);
 
//Funcion que analiza si el disparo le pego a algun asteroide, de ser asi los destruye y asigna puntaje
void procesar_disparos_asteroides(lista_t *lista_disparo, lista_t *lista_asteroides,float *puntos);

//Asigna un puntaje segun el tipo de asteroide que se haya disparado.
void asignar_puntaje(asteroide_t *asteroide,float *puntos);

bool hay_vidas_disponibles(int vidas_disponibles);
void reiniciar_partida(lista_t **lista, int *vidas_disponibles,float *puntos);
float procesar_mejor_puntaje(float *puntajes, size_t nro_partidas);
float generar_aleatorio(float minimo, float maximo);

#endif 
