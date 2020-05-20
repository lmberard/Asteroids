#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "caracteres.h"
#include "diccionario.h"
#include "objetos.h"


#define ARCHIVO_BIN "sprites.bin"
#define CANT_SPRITES 7
#define VENTANA_ANCHO 1000
#define VENTANA_ALTO 700


#define NOMBRE_SPRITE_NAVE "SHIP"
#define NOMBRE_SPRITE_CHORRO "THURST"
#define NOMBRE_SPRITE_AST_1 "ROCK1"
#define NOMBRE_SPRITE_AST_2 "ROCK2"
#define NOMBRE_SPRITE_AST_3 "ROCK3"
#define NOMBRE_SPRITE_AST_4 "ROCK4"
#define NOMBRE_SPRITE_DISPARO "SHOT"

#define ESCALA_DISPARO 3
#define ESCALA_NAVE 1
#define ESCALA_VIDAS 0.6

#define MSJ_BEST_SCORE "BEST SCORE"
#define MSJ_ACTUAL_SCORE "ACTUAL SCORE"
#define MSJ_LIVES "LIVES"

#define PI 3.14159265358979323846

#define ESCALA 1
#define ESCALA_FLECHA 1

#define POS_X_MSJ_ATARI 450
#define POS_Y_MSJ_ATARI 700
#define POS_X_BEST_SCORE 450
#define POS_Y_BEST_SCORE 20
#define POS_X_SCORE 100
#define POS_Y_SCORE 20
#define ESCALA_SCORE 2

#define ESCALA_MSJ 5
#define SEPAR_CARACT_MSJ 25

#define ANGULO_VIDAS PI/2
#define POS_X_VIDAS 100
#define POS_Y_VIDAS 645
#define OFFSET 12



#define ESCALA_DISPARO 3
#define ESCALA_NAVE 1
#define ESCALA_VIDAS 0.6

#define MSJ_BEST_SCORE "BEST SCORE"
#define MSJ_ACTUAL_SCORE "ACTUAL SCORE"
#define MSJ_LIVES "LIVES"

//#define CANT_VIDAS_INICIAL 4
#define ANGULO_VIDAS PI/2
#define POS_X_VIDAS 100
#define POS_Y_VIDAS 645


#define VENTANA_ANCHO 1000
#define VENTANA_ALTO 700

typedef struct{
	char nombre[10];
	uint16_t n;
	const float (*coords)[2];
	}sprite_t;

//dibuja un vector cuyo tamaño es tam_vector con una determinada escala
void dibujar_vector(float **vector, size_t tam_vector, float escala, SDL_Renderer *renderer);

//dibuja la letra utilizando su matriz de coordenadas correspondiente en la posicion (x,y) con una det escala. 
void dibujar_caracter(char letra, SDL_Renderer *renderer, 
					float x, float y, float escala);

//Dibuja una cadena de caracteres en la posicion (x.y) a una determinada escala y separacion entre letras.
void dibujar_palabra(char cadena[], float x_inicial, float y_inicial, float escala, 
					SDL_Renderer *renderer);

//Imprime en la terminal el tiempo y el puntaje con sus respectivas valores. 
void dibujar_parametros(float *puntos, float mejor_puntaje, SDL_Renderer *renderer);

bool dibujar_vidas(SDL_Renderer *r, size_t cant_vidas);

bool graficador_inicializar(const char *fn, int ancho,int alto);
void graficador_finalizar();
bool graficador_dibujar(SDL_Renderer *r,const char *nombre,float escala, float x, float y, float angulo);
void graficador_ajustar_variables(float *x, float *y);

#endif
