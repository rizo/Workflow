all:
	gcc -Wall -O2 -c node.c
	gcc -Wall -O2 -c tree.c
	gcc -Wall -O2 -c funcs.c
	gcc -Wall -O2 -c iotree.c
	gcc -Wall -O2 -c workflow.c

	gcc -o workflow node.o funcs.o tree.o iotree.o workflow.o

exec: all
	./workflow

clean:
	rm -f *.o
	rm workflow
