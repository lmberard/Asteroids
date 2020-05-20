#include "graficador.h"

sprite_t *vector_sprites = NULL;

bool graficador_inicializar(const char *fn, int ancho,int alto)
{
	FILE*f;
	if((f = fopen(fn,"rb"))==NULL)
		return false; 
	for (size_t i=0;!feof(f);i++)
	{
		vector_sprites=(sprite_t*)realloc(vector_sprites,sizeof(sprite_t)*(i+1));

		if(fread(&vector_sprites[i].nombre,sizeof(char)*10, 1, f) != 1)
			return false;
		if(fread(&vector_sprites[i].n,sizeof(uint16_t), 1, f) != 1)
			return false;
		vector_sprites[i].coords =  malloc(sizeof(float)*vector_sprites[i].n*2); 
		
		if(fread((void*)vector_sprites[i].coords,sizeof(float)*vector_sprites[i].n*2, 1, f) != 1)
			return false;
	}	
	if(fclose(f)!=0)
		return false;
	return true;
}

bool graficador_dibujar(SDL_Renderer *r, const char *nombre,float escala, float x, float y, float angulo)
{	
	size_t i=0;
	
	while((strcmp(vector_sprites[i].nombre,nombre)!=0))
	{
		i++;
	}

	for(int j = 0; j < vector_sprites[i].n-1; j++)
	{
		float x1_rot = vector_sprites[i].coords[j][0] *cos(angulo) - vector_sprites[i].coords[j][1] *sin(angulo);
		float y1_rot = vector_sprites[i].coords[j][0] *sin(angulo) + vector_sprites[i].coords[j][1] *cos(angulo);
		float x2_rot =  vector_sprites[i].coords[j+1][0] *cos(angulo) - vector_sprites[i].coords[j+1][1] *sin(angulo);
		float y2_rot =  vector_sprites[i].coords[j+1][0] *sin(angulo) + vector_sprites[i].coords[j+1][1] *cos(angulo);

		SDL_RenderDrawLine(
				r,
				(x1_rot *escala+ x),
				(-y1_rot *escala + VENTANA_ALTO - y),
				(x2_rot *escala+ x),
				(-y2_rot *escala + VENTANA_ALTO - y));
	}	
	return true;
}

void graficador_finalizar()
{
	for(int i=0; i<7; i++)
		free((void *)vector_sprites[i].coords);
}

void graficador_ajustar_variables(float *x, float *y)
{
	if(*x<0){
		*x = -*x;
	}
	if(*y<0){
		*y = -*y;
	}
	
	while(*x > 10.0){
		*x = ((*x) * 0.1);
	}
	while(*y > 10.0){
		*y = (*y / 10.0);
	}
}


void dibujar_vector(float **vector, size_t tam_vector, float escala, SDL_Renderer *renderer)
{
	
	for(int i = 0; i < tam_vector - 1; i++)
					SDL_RenderDrawLine(
						renderer,
						vector[i][0] * escala,
						-vector[i][1] * escala + VENTANA_ALTO,
						vector[i+1][0] * escala,
						-vector[i+1][1] * escala + VENTANA_ALTO
					);	
			
}

void dibujar_caracter(char letra, SDL_Renderer *renderer, float x, float y, float escala)
{
	
	caracteres_t caracter = buscar_matriz_caracter(letra, caracteres, tam_caracteres);
	size_t tam_filas = buscar_filas_caracter(letra, caracteres, tam_caracteres);

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

void dibujar_palabra(char cadena[], float x_inicial, float y_inicial, float escala, SDL_Renderer *renderer)
{
	
	size_t tam_cadena = strlen(cadena);
	size_t i;

	for(i = 0; i < tam_cadena; i++)
		dibujar_caracter(cadena[i], renderer, x_inicial + i*escala*CARACTER_ANCHO, y_inicial, escala);
}


void dibujar_parametros(float *puntos, float mejor_puntaje, SDL_Renderer *renderer)
{
	char aux[30];

	sprintf(aux, "%d",(int)mejor_puntaje);
	dibujar_palabra(aux, POS_X_BEST_SCORE, POS_Y_BEST_SCORE, ESCALA, renderer);
	sprintf(aux, "%d",(int)*puntos);
	dibujar_palabra(aux, POS_X_SCORE, POS_Y_SCORE, ESCALA_SCORE, renderer);

	dibujar_palabra("1979 ATARI INC", POS_X_MSJ_ATARI, POS_Y_MSJ_ATARI, ESCALA, renderer);
}


bool dibujar_vidas(SDL_Renderer *r, size_t cant_vidas)
{
	int offset=0;
	for (size_t i=0;i<cant_vidas;i++)
	{
		if((!graficador_dibujar(r,NOMBRE_SPRITE_NAVE,ESCALA_VIDAS,POS_X_VIDAS + offset,POS_Y_VIDAS,ANGULO_VIDAS)));
		offset += OFFSET;
	}
		
	return true;
}


