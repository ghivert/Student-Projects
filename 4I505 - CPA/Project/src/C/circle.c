#include "circle.h"

struct cl naive(struct pt points[]) {
  size_t size = pts_size(points);
  struct cl circle = circle_nil();

  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++) {
      struct pt p1 = points[i], p2 = points[j];
      if (p1.equal(p1, p2))
        continue;
      bool all_covered = true;
      struct cl temp = new_circle(middle  (p1, p2),
                                  distance(p1, p2) / 2);
      for (size_t k = 0; k < size; k++)
        if (! temp.cover(temp, points[k])) {
          all_covered = false;
          break;
        }
      if (all_covered)
        circle = temp;
    }
  if (! circle.equal(circle, circle_nil()))
    return circle;

  for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++) {
      struct pt p1 = points[i], p2 = points[j];
      if (p1.equal(p1, p2))
        continue;
      for (size_t k = 0; k < size; k++) {
        struct pt p3 = points[k];
        if (p3.equal(p3, p1) ||
            p3.equal(p3, p2))
          continue;
        bool all_covered = true;
        struct cl temp = circum_circle(p1, p2, p3);
        for (size_t l = 0; l < size; l++)
          if (! temp.cover(temp, points[l])) {
            all_covered = false;
            break;
          }
        if (all_covered)
          circle = temp;
      }
    }

  return circle;
}
