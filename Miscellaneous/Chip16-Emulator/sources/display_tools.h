#ifndef _DISPLAY_TOOLS_H_
#define _DISPLAY_TOOLS_H_

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Various functions used to facilitate manipulation of SDL or chip16 internal
   variables. */

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

/* Create blank hidden_registers and blank screen (take height and width to 
   create screen). Free them too. */
hidden_registers * create_registers ();
display_window * create_screen (unsigned int width);
void registers_deallocation (hidden_registers * registers);
void screen_deallocation (display_window * screen);

/* Initialize and free the palette. */
palette initialize_palette ();
void palette_deallocation (palette colors);

/* Print a rectangle in the window. */
SDL_Rect create_rectangle (unsigned int x, unsigned int y, 
			   unsigned int pixel_dimension);

#endif
