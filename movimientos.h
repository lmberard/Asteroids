#ifndef _MOVIMIENTOS_H_
#define _MOVIMIENTOS_H_

#include <stdio.h>
#include <math.h>
#include "config.h"
#include "objetos.h"

//FUNCIONES UTILIZADAS PARA MOVER LA NAVE--------------------------------------------------------------------------
//MOVIMIENTOS.C

//dada la velocidad actual vi, la aceleración a y el paso temporal dt devuelva la velocidad del próximo instante.
float computar_velocidad(float vi, float a, float dt);

//dada la posición actual pi, la velocidad actual vi y el paso temporal dt devuelva la posición del próximo instante.
float computar_posicion(float pi,float vi,float dt);

//dado un vector de n coordenadas modifique cada una de sus componentes mediante la adición del par (dx, dy).
void trasladar_vector(float **v, size_t n, float dx, float dy);

//dado un vector de n coordenadas rote cada una de ella un angulo(en radianes) con respecto al origen de coordenadas.
void rotar_vector(float **v, size_t n, float angulo);

//Función utilizada para chequear que la nave no se vaya de los límites de la pantalla (mundo cilindrico)
void verificar_limites_pantalla(nave_t *nave);

//Inicializa las variables de la nave, utilizada al principio y en cada nueva partida.
void inicializar_valores(fnave_t *nave);

void computar_pot(nave_t *nave);

#endif // _MOVIMIENTOS_H_
