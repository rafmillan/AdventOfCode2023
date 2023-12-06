CFLAGS = -Werror
CC=gcc
# CFLAGS=-Wall -Werror

out:
	$(CC) $(CFLAGS) -o out main.c

clean:
	rm -f out