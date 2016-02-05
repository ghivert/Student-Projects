all: test

test: aps_lan.tab.o aps_lan.lex.o
	gcc -o test $^ -ll
	-./test < ../tests/unit_test.mps

aps_lan.tab.o: aps_lan.tab.c
	gcc -c $<

aps_lan.lex.o: aps_lan.lex.c
	gcc -c $<

aps_lan.lex.c: aps_lan.l
	flex aps_lan.l
	mv lex.yy.c aps_lan.lex.c

aps_lan.tab.c: aps_lan.y
	bison -d aps_lan.y

clean:
	$(RM) aps_lan.tab* aps_lan.lex* test
