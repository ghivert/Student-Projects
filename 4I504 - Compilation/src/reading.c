#include "reading.h"

Code bread_file(char *filename) {
  Code rcode;
  
  FILE *fh = fopen(filename, "rb");
  fseek(fh, 0, SEEK_END);
  rcode.size = ftell(fh);
  rcode.code = malloc(rcode.size);
  fseek(fh, 0, SEEK_SET);
  rcode.code[0] = 0;
  
  fread(rcode.code, 4, rcode.size / 4, fh);
  for (int i = 0; i < rcode.size / 4; i++) {
    rcode.code[i] = ((rcode.code[i] >> 24) & 0xff) | // move byte 3 to byte 0
      ((rcode.code[i] << 8) & 0xff0000) | // move byte 1 to byte 2
      ((rcode.code[i] >> 8) & 0xff00) | // move byte 2 to byte 1
      ((rcode.code[i] << 24) & 0xff000000); // byte 0 to byte 3
  }
  fclose(fh);
  
  return rcode;
}
