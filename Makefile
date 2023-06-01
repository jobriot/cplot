main:
	cc -o main main.c plot.c

test: main
	./main

clean:
	rm -rf *.o main

.PHONY: test clean
