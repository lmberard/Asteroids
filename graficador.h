#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <string.h>

#include "config.h"
#include "objetos.h"

#define ARCHIVO_BIN "sprites.bin"


typedef struct{
	char nombre[10];
	uint16_t n;
	const float (*coords)[2];
	}sprite_t;

bool graficador_inicializar(const char *fn, int ancho,int alto);

bool graficador_dibujar(SDL_Renderer *r,const char *nombre,float escala, float x, float y, float angulo);

#endif