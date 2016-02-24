all: welzl naive

welzl: C/circle.o C/reading.o C/geometry.o C/main.o C/welzl.o
		gcc -O3 -std=c11 -o welzl $^

naive: C/circle.o C/reading.o C/geometry.o C/main.o C/welzl.o
		gcc -O3 -std=c11 -o naive $^

clean:
		$(RM) welzl naive
		cd C
		$(RM) C/*.o
