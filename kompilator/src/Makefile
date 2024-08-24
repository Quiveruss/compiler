#Makefile to create a simple compiler.
#
## Author: Filip Grzankowski

CC=g++
CFLAGS=-Wall -O2

objects = main.o parser.o

compiler: $(objects)
		    $(CC) -o compiler $(objects) -lfl

main.o: main.cpp global.h
		$(CC) -c $<

global.h: parser.h

parser.c parser.h: parser.y
		bison -d -o parser.c $<

.PHONY : clean

clean :
		    -rm -f compiler parser.c parser.h $(objects) 
			
