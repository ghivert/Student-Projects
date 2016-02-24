#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

#include "reading.h"
#include "geometry.h"
#include "circle.h"

// Why C ? Because it's a pretty speed language... ;)
int main(int argc, char const *argv[]) {
  struct dirent *point_file;
  char open_file[4096]; int i;
  DIR *files; FILE *res;

  if (argc < 2) {
    fprintf(stderr, "No directory given... RTFM...\n");
    exit(EXIT_FAILURE);
  }

  files = opendir(argv[1]); res = fopen("results.txt", "w");
  if (!files) {
    fprintf(stderr, "Where's the directory ? Lost in space and time... Do you need a doctor ?\n");
    exit(EXIT_FAILURE);
  }

  while((point_file = readdir(files))) {
    // Because I . and .. does not contain any points file...
    if (strcmp(".", point_file->d_name) == 0 || strcmp("..", point_file->d_name) == 0)
      continue;

    // To ensure keeping the leading path.
    if (argv[1][strlen(argv[1]) - 1] == '/')
      sprintf(open_file, "%s%s", argv[1], point_file->d_name);
    else
      sprintf(open_file, "%s/%s", argv[1], point_file->d_name);

    // Get all points and let's go compute !
    struct pt *points = read_points(open_file);
    struct cl circle = naive(points);
    free_pts(points); // Because I like memory.

    // For the pretty printing.
    int size = strlen(point_file->d_name);
    sprintf(open_file, "%s", point_file->d_name);
    for (i = size; i < 16; i++)
      open_file[i] = ' ';
    open_file[i] = '\0';

    // AND HERE'S THE PRETTY PRINTING ! HELL YEAH !
    fprintf(res, "%s  -- x: %8.4f, y: %8.4f, radius: %8.4f\n", open_file,
                                                            circle.center.x,
                                                            circle.center.y,
                                                            circle.radius);
  }

  // And I'm successful, because I'm worth it.
  fclose(res);
  closedir(files);
  return EXIT_SUCCESS;
}
