CC=gcc
CFLAGS=-g -Wall -std=c99
CLINK=$(CC)
LDFLAGS=-L. -llinked-list
RM=*.o libgrades.so

all: libgrades.so

grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c -fpic grades.c $(LDFLAGS)

libgrades.so: grades.o
	$(CLINK) $(CFLAGS) -shared grades.o -o libgrades.so $(LDFLAGS)

clean:
	 rm -rf $(RM)