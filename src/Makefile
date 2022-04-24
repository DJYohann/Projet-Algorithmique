.PHONY: all clean

CC=gcc
CFLAGS=-Wall

all: prog

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%: %.o 
	$(CC) $(CFLAGS) $^ -o $@

prog: ludotheque.o

depends :
	makedepend -Y *.c

clean:
	rm -f *.o prog