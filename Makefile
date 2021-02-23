CFLAGS = -g
CC = gcc
all: SimpleComputer clean
SimpleComputer: main.o lib.a
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c 
	$(CC) $(CFLAGS) -c -o $@ $<

lib.a: mySimpleComputer.o myTerm.o myBigChars.o
	ar rcs $@ $^

mySimpleComputer.o: mySimpleComputer.c
	$(CC) $(CFLAGS) -c -o $@ $<

myTerm.o: myTerm.c
	$(CC) $(CFLAGS) -c -o $@ $<

myBigChars.o: myBigChars.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -rf *.o
	-rm -rd *.a
