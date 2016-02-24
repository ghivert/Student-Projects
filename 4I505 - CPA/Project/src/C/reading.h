#pragma once

#include <stdio.h>

#include "geometry.h"

#define pts_size(points) ((points - 1)->x)
#define free_pts(points) (free(points - 1))

struct pt *read_points(const char *points_file);

// Huge file, isn't it ?
