#ifndef _DISPARO_H_
#define _DISPARO_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "iterador.h"
#include "juego.h"

#define VELOCIDAD_DISPARO 1000
#define TIEMPO_DISPARO_MAX 0.7

disparo_t* disparo_crear();
void disparo_mover(disparo_t *disparo, float dt);
bool disparo_dibujar(disparo_t *disparo, SDL_Renderer *r);

void cargar_parametros_disparo(disparo_t *nuevo_disparo, nave_t *nave);
void modificar_parametros_disparo(disparo_t *disparo,float dt);

bool tiempo_vida_agotado(disparo_t *disparo);
void eliminar_disparo_agotado(lista_t *lista);

void lista_disparos_modificar(lista_t **lista, float dt, SDL_Renderer *renderer);

float pos_y_disparo(disparo_t *disparo);
void liberar_disparo(disparo_t *disparo);

float pos_x_disparo(disparo_t *disparo);

#endif // _DISPARO_H_
