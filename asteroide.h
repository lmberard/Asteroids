#ifndef _ASTEROIDE_H_
#define _ASTEROIDE_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "iterador.h"

void verificar_limites_pantalla_ast(asteroide_t *asteroide);

//void asteroide_mover(asteroide_t *asteroide, float dt);
bool asteroide_dibujar(asteroide_t *asteroide, SDL_Renderer *r);
void crear_asteroide(lista_t *lista);

void generar_asteroide(asteroide_t *nuevo_asteroide);
void modificar_parametros_asteroide(asteroide_t *asteroide,float dt);

void eliminar_asteroide(struct nodo *nodo, lista_t *lista);

void asteroide_modificar(lista_t *lista, float dt, SDL_Renderer *renderer);
void lista_asteroides_destruir(lista_t *l);

float generar_aleatorio(float minimo, float maximo);
char *asignar_sprite(int numero_sprite);
float asignar_radio(int nro_radio);
#endif // _ASTEROIDE_H_
