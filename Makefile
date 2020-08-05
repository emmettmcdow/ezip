EXE=ezip
CC=g++
DEPS=encrypt_util.hpp decrypt_util.hpp main.hpp
OBJ=encrypt_util.o decrypt_util.o main.o
CFLAGS=-Wall -g0 -I -v

main: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
main.o:  main.cpp decrypt_util.hpp encrypt_util.hpp 
	$(CC) $(CFLAGS) -c main.cpp

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
decrypt_util.o:  decrypt_util.cpp decrypt_util.hpp 
	$(CC) $(CFLAGS) -c decrypt_util.cpp

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
encrypt_util.o:  encrypt_util.cpp encrypt_util.hpp 
	$(CC) $(CFLAGS) -c encrypt_util.cpp

clean: 
	rm -rf $(EXE) *.o 