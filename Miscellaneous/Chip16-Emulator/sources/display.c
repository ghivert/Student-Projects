#include "display.h"

/* Initialize SDL. */
void init_SDL (void) {
  SDL_SetMainReady();
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    fprintf(stderr, "Error during SDL initialization : %s\n",
	    SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

/* Return a SDL_Display initialized with a Renderer and a Window. */
SDL_Display * create_SDL_Display (unsigned int width, unsigned int height) {
  SDL_Display * SDL_Return = malloc (sizeof *SDL_Return);
  
  if (SDL_CreateWindowAndRenderer(width, height, 0, 
				  &(SDL_Return->screen), 
				  &(SDL_Return->renderer)) != 0) {
    fprintf(stderr, "Window not created : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  
  SDL_SetWindowTitle(SDL_Return->screen, "Chip16 - Emulator");
  SDL_SetRenderDrawColor(SDL_Return->renderer, 0, 0, 0, 255);
  SDL_RenderClear(SDL_Return->renderer);
  SDL_RenderPresent(SDL_Return->renderer);
  
  return SDL_Return;
}

/* Free a SDL_DIsplay. */
void SDL_Display_deallocation (SDL_Display * window) {
  free(window->screen);
  free(window->renderer);
  free(window);
}

/* Change the color of the actual brush. Allow to paint on screen with different
   colors. */
void SDL_SetBrush (SDL_Display * window, palette color_palette, 
		   unsigned int index) {
  if (index > 15) {
    fprintf(stderr, "Error, color inexistent.\n");
    exit(EXIT_FAILURE);
  }
  Uint8 red   = (color_palette[index].color & 0xFF0000) >> 16;
  Uint8 green = (color_palette[index].color & 0x00FF00) >> 8;
  Uint8 blue  = (color_palette[index].color & 0x0000FF);
  
  SDL_SetRenderDrawColor(window->renderer, red, green, blue, 255);
}

/* Force the screen to render once again the screen. */
void SDL_ForceRender (SDL_Display * window) {
  SDL_RenderPresent(window->renderer);
}

/* Render a rectangle on the screen. */
void SDL_RenderRectangle (SDL_Display * window, SDL_Rect * trace) {
  SDL_RenderFillRect(window->renderer, trace);
}

/* Quit properly SDL and destroy the window. */
void SDL_Exit (SDL_Display * window) {
  SDL_DestroyWindow(window->screen);
  SDL_Quit();
}
