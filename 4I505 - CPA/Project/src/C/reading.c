#include "reading.h"

// Reads points file, and return a full array of points.
size_t read_points(const char *points_file, struct pt **points) {
  size_t size = 0;
  int x, y;
  *points = malloc(512 * sizeof **points);

  FILE *file = fopen(points_file, "r");

  while (fscanf(file, " %d %d\n", &x, &y) != EOF) {
    (*points)[size++] = new_point(x, y);
  }

  fclose(file);
  // Because I don't like having to manage a variable with size. It's just boring.
  return size;
}
