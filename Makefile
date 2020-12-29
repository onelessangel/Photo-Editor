# Chelcea Claudiu Marian
# WARNING! To work correctly, keep the Makefile separate from the folder of the source code, since the Makefile looks for that specific folder.

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra
OBJ=./FILES/main.o ./FILES/Support.o ./FILES/Memory.o
NAME=app


# define targets
TARGETS=main Support Memory link


# execute
build: 	$(TARGETS) 


# create binary files
main: ./FILES/main.c
	$(CC) $(CFLAGS) -c ./FILES/main.c

Support: ./FILES/Support.c
	$(CC) $(CFLAGS) -c ./FILES/Support.c

Memory: ./FILES/Memory.c
	$(CC) $(CFLAGS) -c ./FILES/Memory.c

# link the files, create executable
link: ./FILES/main.o ./FILES/Support.o ./FILES/Memory.o
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
	rm $(OBJ)

# remove executables
clean:
	rm -f $(TARGETS)

.PHONY: clean
