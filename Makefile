CC = gcc
CFLAGS = -lm
main:
	$(CC) $(CFLAGS) -o main main.c plot.c num.c

test: main
	./main

clean:
	rm -rf *.o main

# main just for convinience
.PHONY: test clean main
