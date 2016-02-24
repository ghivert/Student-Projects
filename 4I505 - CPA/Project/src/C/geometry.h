#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Here's the structures. It's easier with them. :)
struct pt {
  double x;
  double y;

  // Yup, I like Objects.
  double (*distance)  (struct pt, struct pt);
  bool (*equal)       (struct pt, struct pt);
  struct pt (*middle) (struct pt, struct pt);
};

struct cl {
  struct pt center;
  double radius;

  // And I don't mind C++.
  bool (*cover)    (struct cl, struct pt);
  bool (*equal)    (struct cl, struct cl);
  bool (*contains) (struct cl, struct pt);
};

struct pt new_point (double x, double y);
struct cl new_circle(struct pt center, double radius);

double distance(struct pt beg, struct pt end);
struct pt middle  (struct pt beg, struct pt end);

struct cl circum_circle(struct pt fst, struct pt sec, struct pt trd);
