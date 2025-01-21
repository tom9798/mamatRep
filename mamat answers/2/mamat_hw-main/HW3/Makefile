CC=gcc
CFLAGS=-g -Wall -std=c99
CCLINK=$(CC)
OBJS=main.o student.o stack.o
EXEC=prog.exe
RM=rm -f

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

main.o: main.c stack.h student.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

clean:
	$(RM) *.o *.exe