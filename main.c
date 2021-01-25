#include "nave.h"
#include "caracteres.h"
#include "movimientos.h"
#include "vectores.h"
#include "diccionario.h"
#include "graficador.h"
#include "objetos.h"
#include "lista.h"
#include "disparo.h"
#include "asteroide.h"
#include "juego.h"

int main() 
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;
	
	if(graficador_inicializar(ARCHIVO_BIN,VENTANA_ANCHO, VENTANA_ALTO))
		return EXIT_FAILURE;
	
	nave_t *nave = nave_crear();

	int vidas_disponibles = CANT_VIDAS_INICIAL;
	int cant_asteroides = CANT_ASTEROIDES_INICIAL;
	float puntos = 0;
	float mejor_puntaje = 0;
	size_t nro_partida = 0;
	float *puntajes=(float*)malloc(sizeof(float));
	disparo_t* disparo;
	lista_t *lista_disparo = lista_crear(); 	
	lista_t *lista_asteroides = lista_crear();
	int flag =0;
	inicializar_valores(nave);
	cargar_asteroides(lista_asteroides, cant_asteroides);
	
	unsigned int ticks = SDL_GetTicks();
	while(1)
	{
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// ------------------------------------
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						nave->potencia+= INCREMENTO_POTENCIA;	
						flag = 1;	
						break;
					case SDLK_RIGHT:				
						nave->angulo -= NAVE_ROTACION_PASO;
						break;
					case SDLK_LEFT:					
						nave->angulo += NAVE_ROTACION_PASO;
						break;
					case SDLK_SPACE:
						disparo = disparo_crear();
						cargar_parametros_disparo(disparo,nave);
						lista_insertar_final(lista_disparo,disparo);
						break;
				}
				// -------------------------------------------------
			}
			continue;
		}
        		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        		SDL_RenderClear(renderer);
        		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
        		
			// -------------------------------------
			nave_mover(nave, DT);
			lista_disparos_modificar(&lista_disparo, DT, renderer);

			if(flag==1)
				chorro_dibujar(nave,renderer);
			
			procesar_disparos_asteroides(lista_disparo,lista_asteroides,&puntos);
			lista_asteroides_mover_dibujar(lista_asteroides,DT,renderer);
			
			if(nave_dibujar(nave, renderer)==false)
				break;
			
			if(lista_es_vacia(lista_asteroides))
			{
				cant_asteroides += AUMENTO_CANT_ASTEROIDES;
				cargar_asteroides(lista_asteroides, cant_asteroides);
			}
			flag =0;
			if(nave_choca_asteroide(lista_asteroides,nave))
			{	
				if(hay_vidas_disponibles(vidas_disponibles))
				{
					puntajes[nro_partida] = puntos;
					vidas_disponibles --;
	
					dormir = 1500;

					reiniciar_nave(nave,angulo_nave(nave));
				}
				else
				{
					nro_partida ++;
					puntajes = (float*) realloc(puntajes, sizeof(float));
					puntajes[nro_partida]=puntos;

					mejor_puntaje = procesar_mejor_puntaje(puntajes,nro_partida);
					dibujar_palabra("GAME OVER", VENTANA_ANCHO/2, 200, 7, renderer);
					dormir = 1500;
					while(1)
						if(SDL_PollEvent(&event)) 
						{
							if (event.type == SDL_QUIT)
									break;
				
							if (event.type == SDL_KEYDOWN)
								if(event.key.keysym.sym == SDLK_SPACE) 
									break;
						}
					reiniciar_nave(nave,angulo_nave(nave));
					reiniciar_partida(&lista_asteroides,&vidas_disponibles,&puntos);
				}
			}

			dibujar_parametros(&puntos, mejor_puntaje, renderer);
			dibujar_vidas(renderer,vidas_disponibles);
					
		// ----------------------------------------------
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
	// ------------------------------------------------
	graficador_finalizar();
	lista_destruir(lista_disparo,free);
	lista_destruir(lista_asteroides,free);
	free(puntajes);
	nave_liberar(nave);

	// --------------------------------------------------

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
