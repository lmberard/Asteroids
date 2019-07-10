#include "renderizar.h"



void dibujar_vector(float **vector, size_t tam_vector, float escala, SDL_Renderer *renderer){
	
	for(int i = 0; i < tam_vector - 1; i++)
					SDL_RenderDrawLine(
						renderer,
						vector[i][0] * escala,
						-vector[i][1] * escala + VENTANA_ALTO,
						vector[i+1][0] * escala,
						-vector[i+1][1] * escala + VENTANA_ALTO
					);	
			
}

void dibujar_caracter(char letra, const diccionario_t caracteres[], size_t tam, SDL_Renderer *renderer, float x, float y, float escala){
	
	caracteres_t caracter = buscar_matriz_caracter(letra, caracteres, tam);
	size_t tam_filas = buscar_filas_caracter(letra, caracteres, tam);

		for(int i = 0; i < tam_filas - 1; i++){
			SDL_RenderDrawLine(
						renderer,
						caracter[i][0] * escala + x,
						-caracter[i][1] * escala + y,
						caracter[i+1][0] * escala + x,
						-caracter[i+1][1] * escala + y
					);	
		}					
}

void dibujar_palabra(char cadena[], const diccionario_t caracteres[], size_t tam, float x_inicial, float y_inicial, float escala, SDL_Renderer *renderer){
	
	size_t tam_cadena = strlen(cadena);
	size_t i;

	for(i = 0; i < tam_cadena; i++)
		dibujar_caracter(cadena[i], caracteres, tam, renderer, x_inicial + i*escala*CARACTER_ANCHO, y_inicial, escala);
}


void dibujar_parametros(float puntos, float tiempo, 
						const diccionario_t caracteres[], size_t tam_caracteres,
						SDL_Renderer *renderer){

	char aux[30];

	//SCORE
	sprintf(aux, "SCORE %04.f",puntos);
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_1, FILA_1, ESCALA_LETRA , renderer);

	//TIME
	sprintf(aux, "TIME  %04.f", tiempo);
	dibujar_palabra(aux, caracteres, tam_caracteres, COLUM_1, FILA_2, ESCALA_LETRA , renderer);

	//VIDAS
	dibujar_palabra("LIVES", caracteres, tam_caracteres, COLUM_1, FILA_3, ESCALA_LETRA , renderer);

}



bool dibujar_vidas(nave_t *nave, SDL_Renderer *r, size_t cant_vidas)//VALIDAR
{
	int offset=0;
	for (size_t i=0;i<cant_vidas;i++)
	{
	if((graficador_dibujar(r,NOMBRE_SPRITE_NAVE,ESCALA_VIDAS,POS_X_VIDAS + offset,POS_Y_VIDAS,ANGULO_VIDAS))==false);
		offset +=OFFSET;
	}
	return true;
}
