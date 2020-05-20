#ifndef _NAVE_H_
#define _NAVE_H_


#include <SDL2/SDL.h>
#include <stdbool.h>
#include "movimientos.h"
#include "graficador.h"
#include "objetos.h"

#define REDUCCION_POTENCIA 0.1
#define REDUCCION_VELOCIDAD 0.01
#define NAVE_ROTACION_PASO (PI/20)
#define NAVE_X_INICIAL (VENTANA_ANCHO/2)
#define NAVE_Y_INICIAL (VENTANA_ALTO/2)
#define NAVE_VX_INICIAL 0
#define NAVE_VY_INICIAL 0
#define NAVE_ANGULO_INICIAL (PI/2)
#define NAVE_POTENCIA_INICIAL 1
#define INCREMENTO_POTENCIA 1000
#define NAVE_MAX_POTENCIA 10000
#define PI 3.14159265358979323846

//Función utilizada para chequear que la nave no se vaya de los límites de la pantalla (mundo cilindrico)
void verificar_limites_pantalla(nave_t *nave);

//Inicializa las variables de la nave, utilizada al principio y en cada nueva partida.
void inicializar_valores(nave_t *nave);

//Disminuye la potencia un porcentaje y verifica que este en un rango permitido
void computar_pot(nave_t *nave);

nave_t* nave_crear();
void nave_liberar(nave_t *nave);
void nave_mover(nave_t *nave, float dt);
bool nave_dibujar(nave_t *x, SDL_Renderer *r);
bool chorro_dibujar(nave_t *nave, SDL_Renderer *r);

//Se modifican los parametros de la nave en cada iteración segun las teclas que se hayan presionado.
void modificar_parametros_nave(nave_t *nave,float dt);

float pos_x_nave(nave_t* nave);
float pos_y_nave(nave_t* nave);
float angulo_nave(nave_t* nave);
void reiniciar_nave(nave_t *nave, float angulo);

#endif // _NAVE_H_
