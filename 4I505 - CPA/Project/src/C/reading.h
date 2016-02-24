#pragma once

#include <stdio.h>

#include "geometry.h"

#define pts_size(points) ((int)(points - 1)->x)
#define free_pts(points) (free(points - 1))

void read_points(const char *points_file, struct pt points[]);

// Huge file, isn't it ?
