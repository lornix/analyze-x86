CC=gcc
CFLAGS=-O2 -march=native -mtune=native -Wall -Wextra -Wunused

all:
	$(CC) $(CFLAGS) -Iinclude -o analyze-x86 analyze-x86.c

clean:
	rm analyze-x86
