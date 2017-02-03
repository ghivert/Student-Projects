#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <unistd.h>
#include "display_tools.h"

#define SDL_MAIN_HANDLED

/* Each SDL program have to begin with init_SDL(), then must create a 
   SDL_display, and have to finish with SDL_Exit(). */


/* SDL_display is a type used to allow the initialization of SDL_Window and
   SDL_Renderer in one time. It's just a wrapper to simplify the code, and 
   functions call in Racket. */
typedef struct {
  SDL_Window * screen;
  SDL_Renderer * renderer;
} SDL_Display;

/* Initialize SDL. */
void init_SDL (void);

/* Create a SDL_Display : create window and renderer. width and height are 
   useful to give the correct size of window to SDL. */
SDL_Display * create_SDL_Display (unsigned int width, unsigned int height);

/* Free a SDL_Display. */
void SDL_Display_deallocation (SDL_Display * window);

/* Force the screen to update display. */
void SDL_ForceRender (SDL_Display * window);

/* Change the color of the brush to paint in the window. Palette is used to 
   select and define the color, index give the correct index of color. */
void SDL_SetBrush (SDL_Display * window, palette color_palette, 
		   unsigned int index);

/* Render immediatly the trace rectangle on the window. */
void SDL_RenderRectangle (SDL_Display * window, SDL_Rect * trace);

/* Delete the window, and quit properly SDL. */
void SDL_Exit (SDL_Display * window);

#endif
