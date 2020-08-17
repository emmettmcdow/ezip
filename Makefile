EXE=ezip
CC=g++
DEPS=src/encrypt_util.hpp src/decrypt_util.hpp src/main.hpp src/util.hpp
OBJ=encrypt_util.o decrypt_util.o main.o util.o
CFLAGS=-Wall -g -I -v -lboost_system  -lboost_filesystem

main: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
main.o:  src/main.cpp src/decrypt_util.hpp src/encrypt_util.hpp src/util.hpp
	$(CC) -c src/main.cpp $(CFLAGS)

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
decrypt_util.o:  src/decrypt_util.cpp src/decrypt_util.hpp  src/encrypt_util.hpp
	$(CC) -c src/decrypt_util.cpp $(CFLAGS)

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
encrypt_util.o:  src/encrypt_util.cpp src/encrypt_util.hpp 
	$(CC) -c src/encrypt_util.cpp $(CFLAGS)

util.o:  src/util.cpp
	$(CC) -c src/util.cpp $(CFLAGS)

clean: 
	rm -rf $(EXE) *.o *.ezip *.key