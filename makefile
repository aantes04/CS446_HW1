shell: simpleshell.o
	gcc -o shell simpleshell.o

simpleshell.o: simpleshell.c
	gcc -c simpleshell.c

clean:
	rm shell *.o