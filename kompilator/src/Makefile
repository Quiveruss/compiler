# Makefile to create a simple compiler.
#
## Author: Filip Grzankowski

CC=g++
CFLAGS=-Wall -Werror -Wextra

# Objects
objects = main.o parser.o lexer.o symtable.o entry.o

# Main program
compiler: $(objects)
		    $(CC) $(CFLAGS) -o compiler $(objects) -lfl

main.o: main.cpp global.hpp
		$(CC) -c $<

# Global declarations
global.hpp: parser.hpp otherdef.hpp symtable.hpp
symtable.hpp: entry.hpp

# Symbolic table declarations
symtable.o: symtable.cpp symtable.hpp
		$(CC) -c $<

# Entry declarations
entry.o: entry.cpp entry.hpp
		$(CC) $(CFLAGS) -c $<

# Lexer declarations
lexer.cpp: lexer.l
		flex -o lexer.cpp $<

lexer.o: lexer.cpp global.hpp
		$(CC) -c $<

# Parser declarations

parser.cpp parser.hpp: parser.y codegen.cpp
		bison -d -o parser.cpp $<

parser.o: parser.cpp global.hpp
		$(CC) -c $<


# Rest

.PHONY : clean

clean :
		    -rm -f compiler parser.cpp parser.hpp lexer.cpp $(objects) 
