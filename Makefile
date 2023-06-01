CC = gcc
CFLAGS = -lm -D _GNU_SOURCE
main:
	$(CC) $(CFLAGS) -o main main.c plot.c

test: main
	./main

clean:
	rm -rf *.o main

.PHONY: test clean
