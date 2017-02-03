#include "display_tools.h"

/* Create hidden registers of chip16. They're used during display. */
hidden_registers * create_registers () {
  hidden_registers * registers_return = malloc (sizeof *registers_return);
  
  if (!registers_return) {
    fprintf(stderr, "Malloc's bug during hidden_registers allocation.\n");
    exit(EXIT_FAILURE); 
  }

  return registers_return;
}

/* Create a screen, a Renderer and a Window. */
display_window * create_screen (unsigned int width) {
  display_window * screen_return = malloc (sizeof *screen_return);

  if (!screen_return) {
    fprintf(stderr, "Malloc's bug during screen_return allocation.\n");
    exit(EXIT_FAILURE);
  }
  
  screen_return->width = 320;
  screen_return->height = 240;
  screen_return->pixel_dimension = width / 320;
  screen_return->pixels = malloc (320 * sizeof *screen_return->pixels);

  if (!screen_return->pixels) {
    fprintf(stderr, "Malloc's bug during screen_return->pixels allocation.\n");
    exit(EXIT_FAILURE);
  } 
  
  for (int i = 0 ; i < 320 ; i++) {
    (screen_return->pixels)[i] = malloc (240 * sizeof **screen_return->pixels);
    if (!(screen_return->pixels)[i]) {
      fprintf(stderr, "Malloc's bug during (screen_return->pixels)[%d] allocation.\n", i);
      exit(EXIT_FAILURE);
    } 
  }
  return screen_return;
}

void registers_deallocation (hidden_registers * registers) {
  free(registers);
}

void screen_deallocation (display_window * screen) {
  for (int i = 0 ; i < 320 ; i++)
    free((screen->pixels)[i]);
  free(screen->pixels);
  free(screen);
}

/* Initialize the palette with the 16 first colors. */
palette initialize_palette () {
  palette palette_return = malloc (16 * sizeof *palette_return);
  color fill;
  
  if(!palette_return) {
    fprintf(stderr, "Malloc's bug during palette_return allocation.\n");
    exit(EXIT_FAILURE);
  }
  
  fill.color = 0x000000;
  fill.name = "Transparent Black";
  palette_return[0] = fill;
  
  fill.color = 0x000000;
  fill.name = "Black";
  palette_return[1] = fill;
  
  fill.color = 0x888888;
  fill.name = "Gray";
  palette_return[2] = fill;
  
  fill.color = 0xBF3932;
  fill.name = "Red";
  palette_return[3] = fill;
  
  fill.color = 0xDE7AAE;
  fill.name = "Pink";
  palette_return[4] = fill;
  
  fill.color = 0x4C3D21;
  fill.name = "Dark Brown";
  palette_return[5] = fill;
  
  fill.color = 0x905F25;
  fill.name = "Brown";
  palette_return[6] = fill;
  
  fill.color = 0xE49452;
  fill.name = "Orange";
  palette_return[7] = fill;
  
  fill.color = 0xEAD979;
  fill.name = "Yellow";
  palette_return[8] = fill;
  
  fill.color = 0x537A3B;
  fill.name = "Green";
  palette_return[9] = fill;
  
  fill.color = 0xABD54A;
  fill.name = "Light Green";
  palette_return[10] = fill;
  
  fill.color = 0x252E38;
  fill.name = "Dark Blue";
  palette_return[11] = fill;
  
  fill.color = 0x00467F;
  fill.name = "Blue";
  palette_return[12] = fill;
  
  fill.color = 0x68ABCC;
  fill.name = "Light Blue";
  palette_return[13] = fill;
  
  fill.color = 0xBCDEE4;
  fill.name = "Sky Blue";
  palette_return[14] = fill;
  
  fill.color = 0xFFFFFF;
  fill.name = "White";
  palette_return[15] = fill;
  
  return palette_return;
}

/* Free a palette. */
void palette_deallocation (palette colors) {
  free(colors);
}

/* Fill a rectangle as wanted to print it on screen on location (x, y), with a
   dimension of pixel_dimension. */
SDL_Rect create_rectangle (unsigned int x, unsigned int y, 
			   unsigned int pixel_dimension) {
  SDL_Rect rectangle_return;
  
  rectangle_return.x = x * pixel_dimension;
  rectangle_return.y = y * pixel_dimension;
  rectangle_return.w =     pixel_dimension;
  rectangle_return.h =     pixel_dimension;
  
  return rectangle_return;
}
