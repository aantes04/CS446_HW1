shell: simpleshell.o
	gcc -Wall -o shell simpleshell.o

simpleshell.o: simpleshell.c
	gcc -Wall -c simpleshell.c

clean:
	rm -f shell *.o