#Makefile to create a simple compiler.
#
## Author: Filip Grzankowski

CC=g++
CFLAGS=-Wall -O2

# Objects
objects = main.o parser.o lexer.o

# Main program
compiler: $(objects)
		    $(CC) -o compiler $(objects) -lfl

main.o: main.cpp global.hpp
		$(CC) -c $<

# Global declarations
global.hpp: parser.hpp otherdef.hpp

# Symbolic table declarations

symtable.o: symtable.hpp symtable.cpp
		$(CC) -c $<

# Lexer declarations
lexer.cpp: lexer.l
		flex -o lexer.cpp $<

lexer.o: lexer.cpp global.hpp
		$(CC) -c $<

# Parser declarations

parser.cpp parser.hpp: parser.y
		bison -d -o parser.cpp $<

parser.o: parser.cpp global.hpp
		$(CC) -c $<



# Rest

.PHONY : clean

clean :
		    -rm -f compiler parser.cpp parser.hpp lexer.cpp $(objects) 
