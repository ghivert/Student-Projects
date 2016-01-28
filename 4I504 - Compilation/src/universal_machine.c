#include "universal_machine.h"

// Computed GOTO.
#define next()							\
  do {								\
    val = arrays[0].code[pc];					\
    a = (val >> 6) & 0b111;					\
    b = (val >> 3) & 0b111;					\
    c = (val >> 0) & 0b111;					\
    goto *opcodes[get_opc(arrays[0].code[pc++])];     		\
  } while(0)
#define stop() goto end

// Registers.
unsigned int reg[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// Get the opcode.
unsigned int get_opc(unsigned int num) {
  return (num >> 28) & 0b1111;
}

// LET'S GO !
void exec_vm(Code program) {
  unsigned int size = 10;
  Code *arrays = malloc(sizeof *arrays * size);
  for (unsigned int i = 0; i < size; i++)
    arrays[i].size = -1;
  arrays[0] = program;
  
  static void* opcodes[] = {
    &&cmv,     &&aind,    &&aamd, &&add,
    &&mul,     &&div,     &&nand, &&halt,
    &&alloc,   &&abandon, &&out,  &&in,
    &&lprog,   &&orth
  };
  
  unsigned int pc = 0;
  unsigned int val = 0;
  unsigned int a, b, c;
  
  next();
  
 cmv:
  if (reg[c] != 0)
    reg[a] = reg[b];
  next();
  
 aind:
  reg[a] = arrays[b].code[reg[c]];
  next();
  
 aamd:
  arrays[a].code[reg[b]] = reg[c];
  next();
  
 add:
  reg[a] = (reg[b] + reg[c]) % 4294967296; // 2**32.
  next();
  
 mul:
  reg[a] = (reg[b] * reg[c]) % 4294967296;
  next();
  
 div:
  if (reg[c] != 0)
    reg[a] = ((unsigned int) reg[b] / (unsigned int) reg[c]);
  next();
  
 nand:
  reg[a] = ~(reg[b] & reg[c]);
  next();
  
 halt:
  stop();
  
 alloc:
  if (size > reg[b] && arrays[reg[b]].size != -1) {
    fprintf(stderr, "Array collision.\n");
    exit(EXIT_FAILURE);
  }
  
  if (size < reg[b]) {
    Code *arrays_p;
    size = reg[b] + 1;
    if ((arrays_p = realloc(arrays, size)) != NULL) {
      free(arrays);
      arrays = arrays_p;
    } else {
      fprintf(stderr, "Realloc bug.\n");
      exit(EXIT_FAILURE);
    }
  }
  
  Code new;
  new.code = malloc(sizeof *(new.code) * reg[c]);
  new.size = reg[c];
  for (unsigned int i = 0; i < reg[c]; i++)
    new.code[i] = 0;
  arrays[reg[b]] = new;

  next();
  
 abandon:
  free(arrays[reg[c]].code);
  arrays[reg[c]].size = -1;
  next();
  
 out:
  if (reg[c] > 255) {
    fprintf(stderr, "Output : bad number.\n");
    exit(EXIT_FAILURE);
  }
  printf("%c\n", (unsigned char) reg[c]);
  next();
  
 in: 
  {
    char input;
    if ((input = getc(stdin)) == EOF)
      reg[c] = 0xFFFFFFFF;
    else
      reg[c] = input;
    next();
  }
 lprog:
  free(arrays[0].code);

  arrays[0].size = arrays[reg[b]].size;
  arrays[0].code = malloc(sizeof *(new.code) * new.size);
  for (int i = 0; i < new.size; i++)
    arrays[0].code[i] = arrays[reg[b]].code[i];
  pc = reg[c];

  next();
  
 orth:
  reg[(val >> 25) & 0b111] = val & 0x1FFFFFF;
  next();
  
 end:
  return;
}
