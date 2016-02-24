#include "welzl.h"

int nxt_i(int max) {
  return (int)(rand() / (double) RAND_MAX * (max - 1));
}

struct cl b_md(struct pt points[]) {
  struct cl circle;

  if (pts_size(points) >= 3) {
    circle = circum_circle(points[0], points[1], points[2]);
    if (circle.equal(circle, circle_nil()))
      return circle;
  } else if (pts_size(points) == 2) {
    struct pt center = middle(points[0], points[1]);
    double radius = distance(points[0], points[1]) / 2;
    return new_circle(center, radius);
  } else {
    return circle_nil();
  }

  for (size_t i = 0; i < pts_size(points); i++) {
    double dist = points[i].distance(points[i], circle.center) - circle.radius;
    if (!(dist > -2 && dist < 2))
      return circle_nil();
  }

  return circle;
}

struct cl _welzl(struct pt points[], struct pt border[]) {
  srand(time(NULL));
  struct cl circle = circle_nil();

  if (pts_size(points) == 0 || pts_size(border) == 3) {
    circle = b_md(border);
  } else {
    size_t alea = nxt_i(pts_size(points));
    struct pt back = points[alea];

    // Duplicate points, to avoid conflicts.
    struct pt *temp = malloc(sizeof *temp * pts_size(points));
    struct pt *bord = malloc(sizeof *bord * pts_size(border) + 2);
    temp[0].x = pts_size(points) - 1;
    bord[0].x = pts_size(border);
    temp++; bord++;

    // Remove element not needed.
    for (size_t i = 0, cpt = 0; i < pts_size(points) - 1; i++)
      if (i != alea)
        temp[cpt++] = points[i];
    for (size_t i = 0; i < pts_size(border) - 1; i++)
      temp[i] = points[i];

    circle = _welzl(temp, bord);
    if (!circle.equal(circle, circle_nil()) && !circle.contains(circle, back)) {
      bord[(int) pts_size(bord)] = back;
      (bord - 1)->x++;
      circle = _welzl(temp, bord);
    }

    free_pts(temp);
    free_pts(bord);
  }
  return circle;
}

struct cl welzl(struct pt points[]) {
  struct pt start[1];
  start[0].x = 0;
  return _welzl(points, start + 1);
}
