# Chelcea Claudiu Marian

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra
OBJ=main.o Support.o Memory.o
NAME=app


# define targets
TARGETS=main Support Memory link_objects


# execute
build: 	$(TARGETS) 


# create binary files
main: main.c
	$(CC) $(CFLAGS) -c main.c

Support: Support.c
	$(CC) $(CFLAGS) -c Support.c

Memory: Memory.c
	$(CC) $(CFLAGS) -c Memory.c


# link the files, create executable
link_objects: main.o Support.o Memory.o
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
	rm $(OBJ)

# remove executables
clean:
	rm -f $(TARGETS)

.PHONY: clean
