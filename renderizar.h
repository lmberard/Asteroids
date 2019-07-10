
#ifndef _RENDERIZAR_H_
#define _RENDERIZAR_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "caracteres.h"
#include "diccionario.h"

#define FILA_1 20
#define FILA_2 40
#define FILA_3 60

#define COLUM_1 20
#define COLUM_2 650
#define COLUM_3 950
#define ESCALA 1
#define ESCALA_LETRA 1.6
#define ESCALA_FLECHA 1

#define ESCALA_MSJ 5
#define SEPAR_CARACT_MSJ 25


//FUNCIONES PARA RENDERIZAR-----------------------------------------------------------------------------------------
//RENDERIZAR.C

//dibuja un vector cuyo tamaño es tam_vector con una determinada escala
void dibujar_vector(float **vector, size_t tam_vector, float escala, SDL_Renderer *renderer);

//dibuja la letra utilizando su matriz de coordenadas correspondiente en la posicion (x,y) con una det escala. 
void dibujar_caracter(char letra, const diccionario_t caracteres[], size_t tam, 
					SDL_Renderer *renderer, 
					float x, float y, float escala);

//Dibuja una cadena de caracteres en la posicion (x.y) a una determinada escala y separacion entre letras.
void dibujar_palabra(char cadena[], const diccionario_t caracteres[], size_t tam,
					float x_inicial, float y_inicial, float escala, 
					SDL_Renderer *renderer);

//Imprime en la terminal los mensajes SCORE, TIME, FUEL, HORIZONTAL SPEED Y VERTICAL SPEED con sus respectivos valores. 
void dibujar_parametros(float puntos, float tiempo,
						const diccionario_t caracteres[], size_t tam_caracteres, 
						SDL_Renderer *renderer);

bool dibujar_vidas(nave_t *nave, SDL_Renderer *r, size_t cant_vidas);

#endif // _RENDERIZAR_H_
