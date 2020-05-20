#include "vectores.h"


void imprimir_vector(float **v, size_t filas, size_t columnas){

	size_t i, j;

	for(i=0; i<filas; i++){

		for(j=0; j<columnas; j++)			
			printf("% 7f\t", v[i][j]);

		printf("\n");

    }
}

void destruir_vector(float **v, size_t n){

	for(size_t i = 0; i < n; i++)
		free(v[i]);

	free(v);

}

float **crear_vector(size_t n){

	float **v = NULL;
	size_t j;

	v = malloc(n * sizeof(float *));
	if(v == NULL){
		return NULL;
	}
	for(j = 0; j < n; j++){
		v[j] = malloc(COLUMNAS * sizeof(float));

		if(v[j] == NULL){
			destruir_vector(v, j);

			return NULL;
		}
	}

	return v;
}

void copiar_matriz_a_vector(const float m[][COLUMNAS], float **v, size_t n){

	size_t i,j;

	for(i = 0; i < n; i++){

		for(j = 0; j < COLUMNAS; j++) 
			v[i][j] = m[i][j];
	
	}
}

float **matriz_a_vector(const float m[][COLUMNAS], size_t n){

	float **vector = NULL;
	
	//Se uso la funcion de crear_vector porque al ingresar un vector nulo, el realloc funciona como un malloc.
	if(!(vector = crear_vector(n)))
		return NULL;
	
	copiar_matriz_a_vector(m, vector, n);

	return vector;
}


void copiar_valores_a_vector(float **v1, float **v2, size_t filas){

	size_t i,j;

	for(i = 0; i < filas; i++){
		for(j = 0; j < COLUMNAS; j++) 
			v1[i][j] = v2[i][j];
	}
}

void swap(float *v1,float *v2)
{
	float aux = 0;
	aux = *v1;
	*v1 = *v2;
	*v2 = aux;
}




void selection_sort(float *puntajes,size_t nro_partidas)  
{  
    int i, j, min_idx;  
  
 
    for (i = 0; i <nro_partidas-1; i++)  
    {  
        min_idx = i;  
        for (j = i+1; j <nro_partidas; j++) 
       		if (puntajes[j] > puntajes[min_idx])  
            {
            	min_idx = j;  
       			swap(&puntajes[min_idx], &puntajes[i]);  
            }	
    }  
}  
