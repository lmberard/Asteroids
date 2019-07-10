#include "naves.h"
#include "caracteres.h"
#include "movimientos.h"
#include "vectores.h"
#include "diccionario.h"
#include "renderizar.h"
#include "config.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "disparo.h"


int main() {
	//giladas para que aparezca la pantalla del juego
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;
	
	if(graficador_inicializar(ARCHIVO_BIN,VENTANA_ANCHO, VENTANA_ALTO))//Aca levanto todos los sprites del archivo binario
		return EXIT_FAILURE;
	//zona de variables-----------------
	nave_t nave;
	float dt = 1/(float)JUEGO_FPS;
	float tiempo = 0;
	float puntos = 0;

	inicializar_valores(&nave);//Inicializo los valores de la nave
	lista_t *lista_disparo = lista_crear(); //creo la lista de disparos,debo eliminarla al final		
	
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
						computar_pot(&nave);//Aca falta hacer que la potencia sea por un solo instante, osea, un imnpulso, no cte.
						break;
					case SDLK_SPACE:
						crear_disparo(lista_disparo,nave);//Esta funcion crea un disparo y lo agrega a la lista de disparos
						break;
					case SDLK_RIGHT:				
						nave.angulo -= NAVE_ROTACION_PASO;
						break;

					case SDLK_LEFT:					
						nave.angulo += NAVE_ROTACION_PASO;
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
        		nave.potencia -= nave.potencia * 0.1*dt;//Esto no funciona

			nave_mover(&nave, dt);//Muevo la nave en un fx que modifica todos sus parametros

			disparos_modificar(lista_disparo,dt,renderer);//Esta fx modifica los parametros de todos los disparos y en simulatneo los grafica, esto lo hice asi para recorrer la lista una sola vez en vez de varias veces

			tiempo += dt;

			////////////////ZONA DE DIBUJO/////////////////
			dibujar_palabra("ASTEROIDS BY MARTINA Y LUCIA", caracteres, tam_caracteres, 400, 15, ESCALA, renderer);

			if(nave_dibujar(&nave, renderer)==false)
				break;
		
			dibujar_parametros(puntos, tiempo, caracteres, tam_caracteres, renderer);
			////////////////////////////////////////////////
			
			
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
	graficador_finalizar();
	lista_destruir(lista_disparo,free);
	// END código del alumno--------------------------------------------------

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

