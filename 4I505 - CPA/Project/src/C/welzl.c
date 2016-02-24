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

  for (size_t i = 0; i < (size_t)pts_size(points); i++) {
    double dist = (points[i].distance(points[i], circle.center)) - circle.radius;
    if (dist <= -2 && dist >= 2)
      return circle_nil();
  }

  return circle;
}

struct cl _welzl(struct pt points[], struct pt border[]) {
  printf("Null part...\n");
  struct cl circle = circle_nil();
  if (pts_size(points) == 0 || pts_size(border) == 3) {
    printf("La...\n");
    circle = b_md(border);
  } else {
    struct pt  pts[512];
    struct pt bord[512];

    printf("avant back.\n");
    size_t alea = nxt_i(pts_size(points));
    struct pt back = points[alea];
    printf("après back.\n");

    printf("avant assign.\n");
    pts[0] = new_point(pts_size(points) - 1, -1);
    bord[0] = new_point(pts_size(border), -1);
    printf("après assign.\n");

    // Remove element not needed.
    for (size_t i = 0, cpt = 1; i < (size_t)pts_size(points); i++) {
      if (i != alea) {
        pts[cpt++] = points[i];
      }
    }
    printf("Par la.\n");
    for (size_t i = 0, cpt = 1; i < (size_t)pts_size(border); i++) {
      bord[cpt++] = border[i];
    }

    for (size_t i = 1; i < (size_t) pts[0].x + 1; i++)
      printf("(%.2f %.2f) ", pts[i].x, pts[i].y);
    printf("\n");
    for (size_t i = 1; i < (size_t) bord[0].x + 1; i++)
      printf("(%.2f %.2f) ", bord[i].x, bord[i].y);
    printf("\n");

    printf("avant welzl 1.\n");
    circle = _welzl(&(pts[1]), &(bord[1]));
    printf("après welzl 1.\n");

    if (!circle.contains(circle, back)) {
      printf("avant bord.\n");
      bord[((int) bord[0].x) + 1] = back;
      bord[0].x++;
      printf("après bord.\n");

      printf("avant welzl 2.\n");
      circle = _welzl(&(pts[1]), &(bord[1]));
      printf("après welzl 2.\n");
    }
  }
  return circle;
}

struct cl welzl(struct pt points[]) {
  srand(time(NULL));
  struct pt start[1];
  start[0].x = 0;
  return _welzl(points, &(start[1]));
}
