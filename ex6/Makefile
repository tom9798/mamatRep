# Compiler
CC = gcc

# Compiler flags
CFLAGS = -O2 -Wall -fPIC -std=c99

# Source files
SRCS = string.cpp string-array.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = my_program

# Clean command
RM = rm -f

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	$(RM) $(OBJS) $(TARGET)