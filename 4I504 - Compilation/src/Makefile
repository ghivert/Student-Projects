CC=gcc
SRC = main.c reading.c universal_machine.c
OBJ =$(SRC:%.c=%.o)

all: um.exe

um.exe: $(OBJ)
	$(CC) -Wall -Wextra -std=c11 -o $@ $^

%.o: %.c
	$(CC) -Wall -Wextra -std=c11 -c $< -o $@

clean: 
	$(RM) $(OBJ) um.exe

.PHONY: all
