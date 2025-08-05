output: main.o cd.o
	gcc main.o cd.o -o output

main.o: main.c
	gcc -c main.c

cd.o: cd.c 
	gcc -c cd.c

clean:
	rm *.o output
