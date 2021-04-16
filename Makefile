CFLAGS = -g -w
CC = gcc
EXECUTABLE = bin/
SOURCES = src/
OBJECTS = build/mySimpleComputer.o build/myTerm.o build/myBigChars.o build/myReadkey.o build/mySignal.o build/myGUI.o build/ALU.o build/CU.o
.PHONY: all clean
all: bin/SimpleComputer bin/sat bin/sbt cleanBuild

bin/SimpleComputer: build/main.o build/lib.a
	$(CC) $(CFLAGS) -o $@ $^

bin/sat: build/sat.o build/mySimpleComputer.o
	$(CC) $(CFLAGS) -o $@ $^

bin/sbt: build/sbt.o build/rpnTranslator.o
	$(CC) $(CFLAGS) -o $@ $^

build/main.o: src/main.c 
	$(CC) $(CFLAGS) -c -o $@ $<

build/lib.a: $(OBJECTS)
	ar rcs $@ $^

build/mySimpleComputer.o: src/mySimpleComputer.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/myTerm.o: src/myTerm.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/myBigChars.o: src/myBigChars.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/myReadkey.o: src/myReadkey.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/mySignal.o: src/mySignal.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/myGUI.o: src/myGUI.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/ALU.o: src/ALU.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/CU.o: src/CU.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/sat.o: src/sat.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/sbt.o: src/sbt.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/rpnTranslator.o: src/rpnTranslator.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
cleanBuild:
	-rm -rf build/*.o

clean: cleanBuild
	-rm -rf bin/*
