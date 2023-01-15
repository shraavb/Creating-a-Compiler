all: jc

jc: jc.o token.o stack.o
	gcc -g -Wall -std=c11 -o jc jc.o token.o stack.o

token.o: token.c token.h
	gcc -g -Wall -std=c11 -c token.c

jc.o: jc.c jc.h
	gcc -g -Wall -std=c11 -c jc.c

stack.o: stack.c stack.h
	gcc -g -Wall -std=c11 -c stack.c

clean:
	rm -f *.o *~ jc
