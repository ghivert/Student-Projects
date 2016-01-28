#include "universal_machine.h"
#include "reading.h"

int main(int argc, char *argv[]) {
  if (sizeof(int) != 4) {
    fprintf(stderr, "Not 4 bytes...\n");
    exit(EXIT_FAILURE);
  }
  if (argc < 2) {
    fprintf(stderr, "Miss a file...\n");
    exit(EXIT_FAILURE);
  }

  Code program = bread_file(argv[1]);
  exec_vm(program);
  return EXIT_SUCCESS;
}
