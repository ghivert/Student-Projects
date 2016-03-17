SRC = ast_prod.c ast_print.c
OBJ = $(SRC:%.c=%.o)
CFLAGS = -std=c11 -Wall -Wextra

all: ml2c

ml2c: ml2c_lan.tab.o ml2c_lan.lex.o $(OBJ)
	clang $(CFLAGS) -o $@ $^ -ll

ml2c_lan.tab.o: ml2c_lan.tab.c
	clang $(CFLAGS) -c $<

ml2c_lan.lex.o: ml2c_lan.lex.c
	clang $(CFLAGS) -c $<

%.o: %.c
	clang $(CFLAGS) -c $<

ml2c_lan.lex.c: lexer.l
	flex lexer.l
	mv lex.yy.c ml2c_lan.lex.c

ml2c_lan.tab.c: parser.y
	bison -d parser.y
	mv parser.tab.c ml2c_lan.tab.c

clean:
	$(RM) ml2c_lan.tab* ml2c_lan.lex* ml2c $(OBJ) parser.tab.h ../tests/*.out
