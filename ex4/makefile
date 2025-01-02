CC=gcc
CFLAGS=-g -Wall -fPIC -std=c99
LDFLAGS=-shared
OBJS=grades.o
LIB=libgrades.so
RM=rm -f *.o *.so

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $(LIB) $(OBJS) -L. -llinked-list

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c grades.c



clean:
	$(RM) $(OBJS) $(LIB)