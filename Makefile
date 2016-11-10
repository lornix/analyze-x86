CC=gcc
CFLAGS=-O2 -march=native -mtune=native -Wall -Wextra -Wunused

all: analyze-x86

analyze-x86: analyze-x86.c include/*.h
	$(CC) $(CFLAGS) -Iinclude -o analyze-x86 analyze-x86.c

clean:
	rm analyze-x86
