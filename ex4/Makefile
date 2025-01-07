CC=gcc
CFLAGS=-g -Wall -fPIC -std=c99
LDFLAGS=-shared
OBJS=grades.o
LIB=libgrades.so
RM=rm -f

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $(LIB) $(OBJS) -L. -llinked-list

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c grades.c -o grades.o

clean:
	$(RM) $(OBJS) $(LIB)