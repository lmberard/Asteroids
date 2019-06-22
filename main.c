#include "naves.h"
#include "caracteres.h"
#include "movimientos.h"
#include "vectores.h"
#include "diccionario.h"
#include "renderizar.h"
#include "config.h"

int main() {
	//giladas para que aparezca la pantalla del juego
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;

	//zona de variables-----------------
	//EL DIBUJO DE LA NAVE, DE LOS DISPAROS Y DE LOS ASTEROIDES ESTAN EN EL ARCHIVO BINARIO (NO HAY CHORRO)
	/*
	FILE *f;
	if(!(f = fopen ("sprites.bin", rb))
		return EXIT_FAILURE;
	*/
	
	/*HAY QUE HACER UN TDA PARA CADA COSA */
	
	float **vector_nave = NULL;
	size_t nave_tam = sizeof(nave_grande) / sizeof(nave_grande[0]);

	float dt = 1/(float)JUEGO_FPS;
	float tiempo = 0;
	float puntos = 0;
	float angulo, velocidad_x, velocidad_y, posicion_y, posicion_x, x_anterior, potencia;
	inicializar_valores(&posicion_x, &posicion_y, &velocidad_x, &velocidad_y, &angulo, &potencia, &x_anterior);			
	
	//variable para la cantidad de vidas
	//hacer asteroides

	//end zona de variables-------------------------------
	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno------------------------------------
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						if(potencia >= NAVE_MAX_POTENCIA)
							break;
						potencia ++;		
						break;

					case SDLK_SPACE:	
						//ACA TIENE QUE DISPARAR 
						break;

					case SDLK_RIGHT:				
						angulo -= NAVE_ROTACION_PASO;
						break;

					case SDLK_LEFT:					
						angulo += NAVE_ROTACION_PASO;
					break;
				}
				// END código del alumno--------------------------------------------------
			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

		// BEGIN código del alumno-------------------------------------
		
			if(!(vector_nave = matriz_a_vector(nave_grande, nave_tam)))
				return EXIT_FAILURE;

			//ZONA PARA MODIFICAR LAS COSAS
			rotar_vector(vector_nave, nave_tam, angulo);

			modificar_parametros_nave(&x_anterior, &posicion_x, &posicion_y, &velocidad_y, &velocidad_x, &angulo, &dt, &potencia);
			verificar_limites_pantalla(&posicion_x, &posicion_y);

			trasladar_vector(vector_nave, nave_tam, posicion_x, posicion_y);
		
			//ACA HABRIA QUE PONERLE UNA 

			tiempo += dt;

			////////////////ZONA DE DIBUJO/////////////////
			dibujar_palabra("ASTEROIDS BY MARTINA Y LUCIA", caracteres, tam_caracteres, 400, 15, ESCALA, renderer);


			dibujar_vector(vector_nave, nave_tam, ESCALA, renderer);
			//DIBUJAR DISPARO
			//DIBUJAR ASTEROIDES 

			dibujar_parametros(puntos, tiempo, caracteres, tam_caracteres, renderer);
			////////////////////////////////////////////////
			
			destruir_vector(vector_chorro, tam_chorro);
			destruir_vector(vector_nave, nave_tam);

		// END código del alumno----------------------------------------------
        SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);

			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}
	// BEGIN código del alumno------------------------------------------------

	// END código del alumno--------------------------------------------------

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

