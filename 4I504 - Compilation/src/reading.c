#include "reading.h"

Code bread_file(char *filename) {
  Code rcode;
  
  FILE *fh = fopen(filename, "rb");
  fseek(fh, 0, SEEK_END);
  rcode.size = ftell(fh);
  rcode.code = malloc(rcode.size + 1);
  fseek(fh, 0, SEEK_SET);
  fread(rcode.code, 4, rcode.size, fh);
  fclose(fh);
  
  return rcode;
}
