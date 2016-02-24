#include "reading.h"

// Reads points file, and return a full array of points.
void read_points(const char *points_file, struct pt points[]) {
  int x, y, size = 1;
  // struct pt *r_pts = malloc(512 * sizeof *r_pts);

  FILE *file = fopen(points_file, "r");

  while (fscanf(file, " %d %d\n", &x, &y) != EOF) {
    points[size++] = new_point(x, y);
  }

  fclose(file);
  // Because I don't like having to manage a variable with size. It's just boring.
  points[0].x = size - 1;
  points[0].y = -1;
}
