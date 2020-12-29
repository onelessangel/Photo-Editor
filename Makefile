# Chelcea Claudiu Marian

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra
OBJ=main.o Support.o
NAME=app


# define targets
TARGETS=main Support link


# execute
build: 	$(TARGETS) 


# create binary files
main: main.c
	$(CC) $(CFLAGS) -c main.c

Support: Support.c
	$(CC) $(CFLAGS) -c Support.c


# link the files, create executable
link: main.o Support.o
	gcc -o $(NAME) $(OBJ)
	rm $(OBJ)

# remove executables
clean:
	rm -f $(TARGETS)

.PHONY: clean
