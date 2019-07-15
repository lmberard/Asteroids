#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "iterador.h"

////FUNCIONES PARA ANALIZAR SI LA NAVE CHOCO CON ALGUN ASTEROIDE------------

//Esta compara la nave con un solo asteroide
bool nave_choco_con_asteroide(nave_t *nave, asteroide_t *asteroide);

//Esta funcion compara la posicion de la nave con la de cada asteroide, devuelve true si choca con alguno.
bool colisiono_nave_asteroides(nave_t *nave, lista_t *lista_asteroides);

//PROBLEMA
//void comenzar_nueva_vida(nave_t *nave, lista_t *lista_asteroides, SDL_Renderer *renderer);

//PROBLEMAA
//void comenzar_nueva_partida();



///FUNCIONES PARA VERIFICAR SI EL DISPARO LE PEGO AL ASTEROIDE----------------

//Funcion que devuelve true si el disparo se encuentra en una posicion cercana a un solo asteroide(lo choca)
bool disparo_choca_al_asteroide(disparo_t *disparo, asteroide_t *asteroide);
 
//Funcion que analiza si el disparo le pego a algun asteroide, de ser asi los destruye y asigna puntaje
void analizar_disparos(lista_t *lista_disparo, lista_t *lista_asteroides, float *puntos);

//Asigna un puntaje segun el tipo de asteroide que se haya disparado.
void asignar_puntaje(asteroide_t *asteroide, float *puntos);


//Si no hay mas asteroides en la pantalla, esta funcion genera nuevos asteroides pero cada vez que pasa se generan con mas cantidad.
void generar_nuevos_asteroides(lista_t *lista_asteroides, int cant_asteroides);


#endif 
