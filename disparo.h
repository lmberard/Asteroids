#ifndef _DISPARO_H_
#define _DISPARO_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "iterador.h"

//void disparo_mover(disparo_t *disparo, float dt);
bool disparo_dibujar(disparo_t *disparo, SDL_Renderer *r);
void crear_disparo(lista_t *lista, nave_t nave);

void generar_disparo(disparo_t *nuevo_disparo,nave_t nave);
void modificar_parametros_disparo(disparo_t *disparo,float dt);

bool tiempo_vida_agotado(disparo_t *disparo);
void eliminar_disparo(struct nodo *nodo, lista_t *lista);

void disparos_modificar(lista_t *lista, float dt, SDL_Renderer *renderer);

#endif // _DISPARO_H_
