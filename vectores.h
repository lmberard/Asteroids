#ifndef _VECTORES_H_
#define _VECTORES_H_

#include <stdio.h>
#include <stdlib.h>

#define COLUMNAS 2

//genera un vector dinamico de tamaño n. 
float **crear_vector(size_t n);

//recibe una matriz m de Rn×2 y devuelva un vector dinámico con los mismos elementos.
float **matriz_a_vector(const float m[][COLUMNAS], size_t n);

void copiar_matriz_a_vector(const float m[][COLUMNAS], float **v, size_t n);

//Copia los valores de la matriz m al vector dinamico v de n coordenadas.
void copiar_valores_a_vector(float **v1, float **v2, size_t filas);

//intercambia lo apuntado entre dos punteros v1 y v2
void swap(float *v1,float *v2);

//Imprime un vector
void imprimir_vector(float **v, size_t filas, size_t columnas);

//destruye la memoria de un vector v de tamaño n
void destruir_vector(float **v, size_t n);

void selection_sort(float *puntajes,size_t nro_partidas);  

#endif // _VECTORES_H_
