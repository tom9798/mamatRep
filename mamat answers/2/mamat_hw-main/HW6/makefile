CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LDFLAGS =-L. -linput -lfirewall
SOURCES = ip.cpp port.cpp string.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = firewall.exe
RM= *.o *.exe libfirewall.so

all: $(EXECUTABLE) libfirewall.so

libfirewall.so: $(SOURCES)
	$(CXX) $(CXXFLAGS) -shared -fpic $(SOURCES) -o libfirewall.so

firewall.exe: main.o libfirewall.so libinput.so
	$(CXX) $(CXXFLAGS) main.cpp -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(RM)