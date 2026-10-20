CC = cc
CFLAGS = -Wall -Wextra -O2

test: test.c ifstream.c ifstream.h
	$(CC) $(CFLAGS) -o test test.c ifstream.c
	./test

clean:
	rm -f test
