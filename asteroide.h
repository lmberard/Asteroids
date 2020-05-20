#ifndef _ASTEROIDE_H_
#define _ASTEROIDE_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "iterador.h"
#include "juego.h"

#define PI 3.14159265358979323846

#define VELOCIDAD_MAX_ASTEROIDE 15
#define VELOCIDAD_MIN_ASTEROIDE 1
#define RADIO_MIN_ASTEROIDE 8
#define RADIO_MAX_ASTEROIDE 32
#define CANT_ASTEROIDES_SPRITE 4
#define CANT_ASTEROIDES_INICIAL 4
#define AUMENTO_CANT_ASTEROIDES 2
#define RADIO_AST_1 8
#define RADIO_AST_2 16
#define RADIO_AST_3 32

asteroide_t *asteroide_crear();
void asteroide_mover(asteroide_t *asteroide, float dt);
bool asteroide_dibujar(asteroide_t *asteroide, SDL_Renderer *r);
void verificar_limites_pantalla_ast(asteroide_t *asteroide);
float distancia_objeto_asteroide(float posicion_x, float posicion_y, asteroide_t *asteroide);


void generar_asteroides(lista_t *lista, size_t cant_asteroides, int radio_ast, float posicion_x, float posicion_y);
void cargar_asteroides(lista_t *lista, int cant_asteroides);
void cargar_parametros_asteroide(asteroide_t *nuevo_asteroide, float posicion_x, float posicion_y);
void cargar_radio_asteroide(asteroide_t *asteroide , int radio_ast);
float asignar_radio(int nro_radio);

void eliminar_asteroide(nodo_t *nodo, lista_t *lista);

void lista_asteroides_mover_dibujar(lista_t *lista, float dt, SDL_Renderer *renderer);
void lista_asteroides_destruir(lista_t *l);

char *asignar_sprite(int numero_sprite);


void partir_asteroide(lista_t *lista, asteroide_t *asteroide);

void liberar_asteroide(asteroide_t *asteroide);

float radio_ast(asteroide_t *asteroide);


#endif // _ASTEROIDE_H_
