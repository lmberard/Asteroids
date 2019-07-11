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
		vector_sprites[i].coords =  malloc(sizeof(float)*vector_sprites[i].n*2); //Aca estoy pidiendo memoria que tengo que liberar despues
		if(fread(vector_sprites[i].coords,sizeof(float)*vector_sprites[i].n*2, 1, f) != 1)
			return false;
	}	
	if(fclose(f)!=0)
		return false;
	return true;
}

/*Esta funcion está re villera pero porque me confundia mil haciendo todas esas operaciones en la misma linea, igual funca */
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

void graficador_finalizar()//esta funcion está mal
{
	for(size_t i=0; i<=7;i++)//Harcodeado
	{
		free(vector_sprites[i].coords);
	}
	free(vector_sprites);
}
