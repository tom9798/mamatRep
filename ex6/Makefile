# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -fPIC -std=c++11

# Source files
SRCS = string.cpp string-array.cpp main.cpp generic-string.h string-array.h string.h

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
	$(CXX) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	$(RM) $(OBJS) $(TARGET)