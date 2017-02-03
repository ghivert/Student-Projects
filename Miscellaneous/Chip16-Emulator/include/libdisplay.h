#ifndef _LIBDISPLAY_H_
#define _LIBDISPLAY_H_

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define SDL_MAIN_HANDLED

/* Various functions used to facilitate manipulation of SDL or chip16 internal
   variables. Each SDL program have to begin with init_SDL(), then must create a
   SDL_display, and have to finish with SDL_Exit(). */

/* Palette of colors. Palette is an array of 16 different colors. 
   Each color is defined by its hex-value 0xRRGGBB, with RR value for red, 
   GG value for green and BB value for blue. Name just here for convenient
   debugging. */
typedef struct {
  unsigned int color;
  char * name;
} color;
typedef color * palette;

/* Hidden registers of chip16. 
   They're not directly modifiable, but they are useful to graphics state. 
   Struct allow to manipulate them easily and pass them quickly to Racket. */
typedef struct {
  unsigned int bg : 4;
  unsigned char spritew;
  unsigned char spriteh;
  bool hflip;
  bool vflip;
} hidden_registers;

/* Display window contains everything needed to emulate a screen. */
typedef struct {
  unsigned int width;
  unsigned int height;
  unsigned int pixel_dimension;
  unsigned char ** pixels;
  color brush;
} display_window;

/* SDL_display is a type used to allow the initialization of SDL_Window and
   SDL_Renderer in one time. It's just a wrapper to simplify the code, and 
   functions call in Racket. */
typedef struct {
  SDL_Window * screen;
  SDL_Renderer * renderer;
} SDL_Display;

/* Create blank hidden_registers and blank screen (take height and width to 
   create screen). Free them too. */
extern hidden_registers * create_registers ();
extern display_window * create_screen (unsigned int width);
extern void registers_deallocation (hidden_registers * registers);
extern void screen_deallocation (display_window * screen);

/* Initialize and free the palette. */
extern palette initialize_palette ();
extern void palette_deallocation (palette colors);

/* Print a rectangle in the window. */
extern SDL_Rect create_rectangle (unsigned int x, unsigned int y, 
				  unsigned int pixel_dimension);

/* Initialize SDL. */
extern void init_SDL (void);

/* Create a SDL_display : create window and renderer. width and height are 
   useful to give the correct size of window to SDL. */
extern SDL_Display * create_SDL_Display (unsigned int width, unsigned int height);
/* Free a SDL_Display. */
extern void SDL_Display_deallocation (SDL_Display * window);

/* Force the screen to update display. */
extern void SDL_ForceRender (SDL_Display * window);

/* Change the color of the brush to paint in the window. Palette is used to 
   select and define the color, index give the correct index of color. */
extern void SDL_SetBrush (SDL_Display * window, palette color_palette, 
			  unsigned int index);

/* Render immediatly the trace rectangle on the window. */
extern void SDL_RenderRectangle (SDL_Display * window, SDL_Rect * trace);

/* Delete the window, and quit properly SDL. */
extern void SDL_Exit (SDL_Display * window);

#endif
