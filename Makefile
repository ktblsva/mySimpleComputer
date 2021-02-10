CFLAGS = -Wall -Werror
CC = gcc
all: prog clean
prog: main.o lib.a
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c 
	$(CC) $(CFLAGS) -c -o $@ $<

lib.a: mySimpleComputer.o
	ar rcs $@ $^

mySimpleComputer.o: mySimpleComputer.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include main.d mySimpleComputer.d 

clean:
	-rm -rf *.o
	-rm -rd *.a