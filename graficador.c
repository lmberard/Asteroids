#include "graficador.h"

sprite_t *vector_sprites = NULL;

bool graficador_inicializar(const char *fn, int ancho,int alto)
{
	//fprintf(stderr,"hola\n");
	FILE*f;
	//fprintf(stderr,"ENTRO A GRAF graficador_inicializarn\n" );
	if((f = fopen(fn,"rb"))==NULL)
		return false; 
	//fprintf(stderr, "abrio el archivo\n" );
	for (size_t i=0;!feof(f);i++)
	{
		vector_sprites=(sprite_t*)realloc(vector_sprites,sizeof(sprite_t)*(i+1));

		if(fread(&vector_sprites[i].nombre,sizeof(char)*10, 1, f) != 1)
			return false;

	//fprintf(stderr, "Leyo nombre %s en I=%d\n",vector_sprites[i].nombre,i);//estos fprintf los dejé por si despues falla algo, cuando ya este todo ok los volamos
		
		if(fread(&vector_sprites[i].n,sizeof(uint16_t), 1, f) != 1)
			return false;
	//	fprintf(stderr, "Leyo n =%d\n",vector_sprites[i].n);
		
		vector_sprites[i].coords =  malloc(sizeof(float)*vector_sprites[i].n*2); //Aca estoy pidiendo memoria que tengo que liberar despues

		if(fread(vector_sprites[i].coords,sizeof(float)*vector_sprites[i].n*2, 1, f) != 1)
			return false;
	//	fprintf(stderr, "Leyo coords\n");

		/*for (int k=0; k< vector_sprites[i].n; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				printf("n:% f\t",vector_sprites[i].coords[k][j]);
			}
		printf("\n");
		}*/
	}	
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

/*
bool graficador_dibujar(SDL_Renderer *r, const char *nombre, float escala, float x, float y, float angulo)
{	
	lista_t l;
	iterador_t *iterador = iterador_crear(l);
	struct nodo *nodo_modulo = iterador_actual(iterador);//me paro en el primer nodo
	
	if(nodo_modulo->dato.nombre != nombre)//mientras que no encuentre una coincidencia, avanzo
	{fprintf(stderr, "nombre= %s nodo_modulo->dato.nombre  =%s\n",nombre,nodo_modulo->dato.nombre );
		if((iterador_siguiente(iterador))==false)//avanzo al siguiente nodo
			break;

		nodo_modulo = iterador_actual(iterador);
	}

		for(int i = 0; i < nodo_modulo->dato.n - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				nodo_modulo->dato.cords[i][0] * escala + x / 2,//dato tiene la fila del nodo actual
				-nodo_modulo->dato.cords[i][1] * escala + y / 2,
				nodo_modulo->dato.cords[i+1][0] * escala + x / 2,//dato.cords[i][0] tiene todas las x se la mtriz
				-nodo_modulo->dato.cords[i+1][1] * escala + y / 2
			);


	//destruir(l, free());
	iterador_destruir(iterador);

	return true;
}
*/
