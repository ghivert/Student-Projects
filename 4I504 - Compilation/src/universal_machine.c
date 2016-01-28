#include "universal_machine.h"

// Opcode.
#define get_opc(num) (num >> 28) & 0b1111

// Computed GOTO.
#define next()						\
  do {							\
    val = arrays[0].code[pc];				\
    a = (val >> 6) & 0b111;				\
    b = (val >> 3) & 0b111;				\
    c = (val >> 0) & 0b111;				\
    goto *opcodes[get_opc(arrays[0].code[pc++])];	\
  } while(0)
#define stop() goto end

// Registers.
unsigned int reg[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// Get the opcode.

#define debug(opcode) ;//printf("%s, pc = %x,\n\ta = %d, b = %d, c = %d \n", opcode, pc, reg[a], reg[b], reg[c])

// LET'S GO !
void exec_vm(Code program) {
  unsigned int size = 10, arr = 1;
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
  debug("cmv");
  if (reg[c] != 0)
    reg[a] = reg[b];
  next();

 aind:
  debug("aind");
  printf("%d\n", reg[b]);
  reg[a] = arrays[reg[b]].code[reg[c]];
  next();

 aamd:
  debug("aamd");
  arrays[reg[a]].code[reg[b]] = reg[c];
  next();

 add:
  debug("add");
  reg[a] = (reg[b] + reg[c]) % 4294967296; // 2**32.
  next();

 mul:
  debug("mul");
  reg[a] = (reg[b] * reg[c]) % 4294967296;
  next();

 div:
  debug("div");
  if (reg[c] != 0)
    //printf("%ld %ld %08x\n", reg[a], reg[b], (unsigned int) reg[c]);
    //printf("%d\n", reg[b] / reg[c]);
    reg[a] = ((unsigned int) reg[b] / (unsigned int) reg[c]);
  next();

 nand:
  debug("nand");
  reg[a] = ~(reg[b] & reg[c]);
  next();

 halt:
  debug("halt");
  stop();

 alloc:
  debug("alloc");

  if (size < arr) {
    Code *arrays_p;
    size = size * 2;
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
  arrays[size] = new;
  reg[b] = size++;

  next();

 abandon:
  debug("abandon");
  free(arrays[reg[c]].code);
  arrays[reg[c]].size = -1;
  next();

 out:
  debug("out");
  if (reg[c] > 255) {
    fprintf(stderr, "Output : bad number.\n");
    exit(EXIT_FAILURE);
  }
  printf("%c", (unsigned char) reg[c]);
  next();

 in:
  printf("in");
  {
    char input;
    if ((input = getc(stdin)) == EOF)
      reg[c] = 0xFFFFFFFF;
    else
      reg[c] = input;
    next();
  }
 lprog:
  debug("lprog");
  if (reg[b] != 0) {
    Code temp;
    temp.size = arrays[reg[b]].size;
    temp.code = malloc(sizeof *(temp.code) * temp.size);
    //printf("Ici\n");
    for (int i = 0; i < temp.size; i++)
      temp.code[i] = arrays[reg[b]].code[i];
    free(arrays[0].code);
    //printf("Ou la.\n");
    arrays[0] = temp;
  }
  pc = reg[c];

  next();

 orth:
  debug("orth");
  reg[(val >> 25) & 0b111] = val & 0x1FFFFFF;
  next();

 end:
  return;
}
