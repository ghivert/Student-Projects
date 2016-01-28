#include <stdio.h>
#include <stdlib.h>

#ifndef __UNIVERSAL__
#define __UNIVERSAL__

typedef struct {
  long size;
  unsigned int *code;
} Code;

void exec_vm(Code program);

#endif
