#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Macros for easy access.
#define get_opc(num) (num >> 28) & 0b1111
#define next()					\
  do {						\
    val = memory[0][pc];			\
    a = (val >> 6) & 0b111;			\
    b = (val >> 3) & 0b111;			\
    c = (val >> 0) & 0b111;			\
  } while(0)
#define stop() return

// Accessors for arrays.
#define size_arr(arr) *(arr - 1)
#define free_arr(arr) free(arr - 1)

// Every opcodes.
enum opcodes {CMV,   AIND,    AAMD, ADD, 
	      MUL,   DIV,     NAND, HALT, 
	      ALLOC, ABANDON, OUT,  IN, 
	      LPROG, ORTH};

// Registers.
unsigned int reg[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

unsigned int * bread_file(char *filename) {
  // Read the entire binary file, and return it, as array of bytes.
  unsigned int *rcode, size;
  
  // End of file and adequate array size.
  FILE *fh = fopen(filename, "rb");
  fseek(fh, 0, SEEK_END);
  size = ftell(fh);
  fseek(fh, 0, SEEK_SET);
  
  rcode = calloc(sizeof *rcode, size / 4 + 1);
  rcode[0] = size / 4;
  fread(rcode + 1, 4, size / 4, fh);
  
  // Reverse endianess.
  for (unsigned int i = 0; i < size / 4; i++)
    rcode[i] = ((rcode[i] >> 24) & 0x000000ff) | 
      ((rcode[i] << 8)  & 0x00ff0000)          | 
      ((rcode[i] >> 8)  & 0x0000ff00)          | 
      ((rcode[i] << 24) & 0xff000000);
  fclose(fh);
  
  return rcode + 1;
}

void exec_vm(unsigned int *program) {
  char input;
  int index = 0, temp;
  unsigned int size = 1 >> 26;
  unsigned int *new, *temp3;
  unsigned int **memory = calloc(sizeof *memory, size);
  
  unsigned int pc = 0;
  unsigned int val = 0;
  unsigned int a, b, c;
  
  // Program array in 0.
  memory[0] = program;
  
  // Main loop.
  while(1) {
    // Values for A, B and C.
    next();
    
    // LET'S SWITCH ! (No computed goto, because... No reason ! :) )
    switch (get_opc(memory[0][pc++])) {
    case CMV:
      if (reg[c] != 0)
	reg[a] = reg[b];
      break;
      
    case AIND:
      reg[a] = memory[reg[b]][reg[c]];
      break;

    case AAMD:
      memory[reg[a]][reg[b]] = reg[c];
      break;

    case ADD:
      reg[a] = (reg[b] + reg[c]) % 4294967296; // 2**32.
      break;

    case MUL:
      reg[a] = (reg[b] * reg[c]) % 4294967296;
      break;

    case DIV:
      if (reg[c] != 0)
	reg[a] = (reg[b] / reg[c]);
      break;

    case NAND:
      reg[a] = ~(reg[b] & reg[c]);
      break;

    case HALT:
      stop();

    case ALLOC:
      // Search for first free place.
      for (temp = index - 1; index != temp; index = (index + 1) % size)
	if (!memory[index])
	  break;
      
      // No free place, realloc memory.
      if (index == temp) {
	index = size; size *= 2;
	if (!(memory = realloc(memory, sizeof *memory * size))) {
	  fprintf(stderr, "Realloc failure.\n");
	  exit(EXIT_FAILURE);
	}
      }
      
      // Finally alloc.
      new = calloc(sizeof *new, (reg[c] + 1));
      new[0] = reg[c];
      reg[b] = index;
      memory[index] = new + 1;
      break;

    case ABANDON:
      free_arr(memory[reg[c]]);
      memory[reg[c]] = NULL;
      break;
      
    case OUT:
      if (reg[c] > 255) {
	fprintf(stderr, "Output : bad number.\n");
	exit(EXIT_FAILURE);
      }
      printf("%c", (unsigned char) reg[c]);
      break;

    case IN:
      if ((input = getc(stdin)) == EOF)
	reg[c] = 0xFFFFFFFF;
      else
	reg[c] = input;
      break;
      
    case LPROG:
      // If reg[B] = 0, just change the pc. Else, just carbon copy.
      if (reg[b] != 0) {	
	temp3 = malloc(sizeof *temp3 * (size_arr(memory[reg[b]]) + 1));
	temp3[0] = size_arr(memory[reg[b]]);
	temp3 = temp3 + 1;
	for (unsigned int i = 0; i < size_arr(temp3); i++)
	  temp3[i] = memory[reg[b]][i];
	free_arr(memory[0]);
	memory[0] = temp3;
      }
      
      pc = reg[c];
      break;

    case ORTH:
      reg[(val >> 25) & 0b111] = val & 0x1FFFFFF;
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  // Cause I want to run ! :)
  if (sizeof(int) != 4) {
    fprintf(stderr, "Not 4 bytes...\n");
    exit(EXIT_FAILURE);
  }
  
  if (argc < 2) {
    fprintf(stderr, "Miss a file...\n");
    exit(EXIT_FAILURE);
  }
  
  unsigned int *program = bread_file(argv[1]);
  exec_vm(program);
  return EXIT_SUCCESS;
}
