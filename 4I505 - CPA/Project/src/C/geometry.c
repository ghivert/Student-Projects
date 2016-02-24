#include "geometry.h"
#include <stdio.h>
#include <math.h>

// Many functions for creating points or circle, or making a circumscribed circle...
// Really, you don't need to read this...
// But if you REALLY want... Just go ahead. You cant say I didn't warned you...

double p_distance(struct pt self, struct pt point) {
  return sqrt(pow(self.x - point.x, 2) + pow(self.y - point.y, 2));
}

bool p_equal(struct pt self, struct pt point) {
  return self.x == point.x && self.y == point.y;
}

struct pt p_middle  (struct pt self, struct pt point) {
  return new_point((self.x + point.x) / 2, (self.y + point.y) / 2);
}

struct pt new_point (double x, double y) {
  return (struct pt) { x, y, p_distance, p_equal, p_middle };
}

bool c_cover(struct cl self, struct pt point) {
  return self.center.distance(self.center, point) <= self.radius;
}

bool c_equal(struct cl self, struct cl circle) {
  return self.center.equal(self.center, circle.center) && self.radius == circle.radius;
}
bool c_contains(struct cl self, struct pt point) {
  return self.center.distance(self.center, point) < self.radius;
}

struct cl new_circle(struct pt center, double radius) {
  return (struct cl) { center, radius, c_cover, c_equal, c_contains};
}

double distance(struct pt beg, struct pt end) {
  return p_distance(beg, end);
}
struct pt middle  (struct pt beg, struct pt end) {
  return p_middle(beg, end);
}

// You can't understand this. It works, trust me : I have some cake for you.
struct cl circum_circle(struct pt fst, struct pt sec, struct pt trd) {
  double x1 = fst.x, x2 = sec.x, x3 = trd.x;
  double y1 = fst.y, y2 = sec.y, y3 = trd.y;

  if ((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) == 0) {
    return circle_nil();
  }

  double x = (((x3*x3 - x2*x2 + y3*y3 - y2*y2) / (2 * (y3 - y2))) - ((x2*x2 - x1*x1 + y2*y2 - y1*y1) / (2 * (y2 - y1)))) / (((x2 - x1) / (y2 - y1)) - ((x3 - x2) / (y3 - y2)));

  double y = (-((x2 - x1) / (y2 - y1))) * x + ((x2*x2 - x1*x1 + y2*y2 - y1*y1) / (2 * (y2 - y1)));

  double r = sqrt(pow(x1 - x, 2) + pow(y2 - y1, 2));

  return new_circle(new_point(x, y), r);
}
