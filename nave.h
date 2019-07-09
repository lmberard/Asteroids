#ifndef _NAVE_H_
#define _NAVE_H_


#include <SDL2/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"


void nave_mover(nave_t *nave, float dt);
bool nave_dibujar(nave_t *x, SDL_Renderer *r);
//Se modifican los parametros de la nave en cada iteración segun las teclas que se hayan presionado.
void modificar_parametros_nave(nave_t *nave,float dt);

#endif // _NAVE_H_
