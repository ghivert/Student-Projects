#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "reading.h"
#include "geometry.h"
#include "circle.h"
#include "welzl.h"

// For benchmark.
double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec * 1e-6;
}

// Why C ? Because it's a rather speed language... ;)
int main(int argc, char const *argv[]) {
  srand(time(NULL));

  double elapsed_time;
  bool pretty = true, custom_file = false;
  char open_file[4096];
  DIR *files;
  FILE *res;
  struct dirent *point_file;

  if (argc < 2) {
    fprintf(stderr, "No directory given... RTFM...\n");
    exit(EXIT_FAILURE);
  } else if (argc > 3)
    custom_file = true;

  files = opendir(argv[1]);

#ifdef _NAIVE
  if (!custom_file)
    res = fopen("results_naive.csv", "w");
  else
    res = fopen(argv[3], "w");
#else
  if (!custom_file)
    res = fopen("results_welzl.csv", "w");
  else
    res = fopen(argv[3], "w");
#endif

  if (!files) {
    fprintf(stderr, "Where's the directory ? Lost in time and space... Do you need a doctor ?\n");
    exit(EXIT_FAILURE);
  }

  while((point_file = readdir(files))) {
    // Because . and .. does not contain any points file...
    if (strcmp(".", point_file->d_name) == 0 || strcmp("..", point_file->d_name) == 0)
      continue;

    // To ensure keeping the leading path.
    if (argv[1][strlen(argv[1]) - 1] == '/')
      sprintf(open_file, "%s%s", argv[1], point_file->d_name);
    else
      sprintf(open_file, "%s/%s", argv[1], point_file->d_name);

    // Get all points and let's go compute !
    struct pt *points;
    size_t size_tmp = read_points(open_file, &points);
    elapsed_time = get_time();

#ifdef _NAIVE
    struct cl circle = naive(points, size_tmp);
#else
    struct cl circle = welzl(points, size_tmp);
#endif

    elapsed_time = get_time() - elapsed_time;
    free(points);

    if (argc > 2) {
      if (strcmp(argv[2], "pretty") == 0) {
        pretty = true;
      } else {
        pretty = false;
      }
    }

    if (pretty) {
      // For the pretty printing.
      int size = strlen(point_file->d_name), i;
      sprintf(open_file, "%s", point_file->d_name);
      for (i = size; i < 16; i++)
	open_file[i] = ' ';
      open_file[i] = '\0';

      // AND HERE'S THE PRETTY PRINTING ! HELL YEAH !
      fprintf(res, "%s  -- x: %10.4f, y: %10.4f, radius: %10.4f, time: %10.4f\n",
	      open_file,
	      circle.center.x,
	      circle.center.y,
	      circle.radius,
	      elapsed_time);
      fflush(res);
    } else {
      fprintf(res, "%10.4f,%10.4f,%10.4f,%10.4f\n",
	      circle.center.x,
	      circle.center.y,
	      circle.radius,
	      elapsed_time);
      fflush(res);
    }
  }

  // And I'm successful, because I'm worth it.
  fclose(res);
  closedir(files);
  return EXIT_SUCCESS;
}
