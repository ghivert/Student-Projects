#include "welzl.h"

// Get a random int.
int nxt_i(int max) {
  return (int)(rand() / (double) RAND_MAX * (max - 1));
}

// Do the b_md calculus.
struct cl b_md(struct pt points[], int size) {
  if (size >= 4)
    printf("Waouh\n");
  if (size == 3) {
    return circum_circle(points[0], points[1], points[2]);
  } else if (size == 2) {
    struct pt center = middle(points[0], points[1]);
    double radius    = distance(points[0], center);
    return new_circle(center, radius);
  } else if (size == 1) {
    return new_circle(points[0], 0);
  }
  return new_circle(new_point(0, 0), -2);
}

// Cause there's an algorithm.
struct cl _welzl(struct pt points[], struct pt border[], size_t size_points, size_t size_border) {
  // Duplicates points.
  {
    struct pt *pts = calloc(512, sizeof *pts);
    struct pt *bor = calloc(512, sizeof *bor);

    memcpy(pts, points, sizeof *pts * size_points);
    memcpy(bor, border, sizeof *bor * size_border);

    points = pts;
    border = bor;
  }

  // Initiliazes the empty circle.
  struct cl circle;

  // And begins.
  if (size_points == 0 || size_border == 3) {
    circle = b_md(border, size_border);
  } else {
    // Pick a random point and remove it from points.
    size_t alea    = nxt_i(size_points);
    struct pt back = points[alea];
    points[alea]   = points[--size_points];

    // Recursive call.
    circle = _welzl(points, border, size_points, size_border);

    // Test if another recursive call is needed.
    if (circle.equal(circle, new_circle(new_point(0, 0), -2)) || !circle.contains(circle, back)) {
      border[size_border++] = back;
      circle = _welzl(points, border, size_points, size_border);
    }
  }

  // And free the memory and return.
  free(points);
  free(border);
  return circle;
}

struct cl welzl(struct pt points[], size_t size) {
  struct pt *start = malloc(sizeof *start * size);
  return _welzl(points, start, size, 0);
}
