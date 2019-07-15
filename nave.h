#ifndef _NAVE_H_
#define _NAVE_H_


#include <SDL2/SDL.h>
#include <stdbool.h>
#include "config.h"
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"

//Función utilizada para chequear que la nave no se vaya de los límites de la pantalla (mundo cilindrico)
void verificar_limites_pantalla(nave_t *nave);

//Inicializa las variables de la nave, utilizada al principio y en cada nueva partida.
void inicializar_valores(nave_t *nave);

//Disminuye la potencia un porcentaje y verifica que este en un rango permitido
void computar_pot(nave_t *nave);

void nave_mover(nave_t *nave, float dt);
bool nave_dibujar(nave_t *x, SDL_Renderer *r);
//Se modifican los parametros de la nave en cada iteración segun las teclas que se hayan presionado.
void modificar_parametros_nave(nave_t *nave,float dt);

#endif // _NAVE_H_
