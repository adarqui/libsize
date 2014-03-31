all:
	make clean
	gcc -Wall -O3 -I inc libsize.c -c
	gcc -Wall -O3 -I inc -lm libsize.o ex1.c -o ex1

clean:
	rm -f *.o ex1

test:
	echo hi
