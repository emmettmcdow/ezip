EXE=ezip
CC=g++
DEPS=src/encrypt_util.hpp src/decrypt_util.hpp src/main.hpp
OBJ=encrypt_util.o decrypt_util.o main.o
CFLAGS=-Wall -g0 -I -v

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
main.o:  src/main.cpp src/decrypt_util.hpp src/encrypt_util.hpp 
	$(CC) $(CFLAGS) -c src/main.cpp

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
decrypt_util.o:  src/decrypt_util.cpp src/decrypt_util.hpp 
	$(CC) $(CFLAGS) -c src/decrypt_util.cpp

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
encrypt_util.o:  src/encrypt_util.cpp src/encrypt_util.hpp 
	$(CC) $(CFLAGS) -c src/encrypt_util.cpp

clean: 
	rm -rf $(EXE) *.o 