CC = cc
CFLAGS = -Wall -Wextra -O2

test: test.c ifstream.h
	$(CC) $(CFLAGS) -o test test.c
	./test

clean:
	rm -f test
