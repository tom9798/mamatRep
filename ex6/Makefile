CXX=g++
CXXLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11 -fpic
LDFLAGS = -shared
OBJS=string.o ip.o port.o main.o string-array.o
LIBS = -lfirewall -L. -linput -L.
EXEC=firewall.exe
RM=rm -rf

$(EXEC): $(OBJS) libfirewall.so	libinput.so
	$(CXXLINK) $(OBJS) -o $(EXEC) libfirewall.so libinput.so -L.

libfirewall.so: string.o ip.o port.o string-array.o	main.o
	$(CXXLINK) $(LDFLAGS) string.o ip.o port.o string-array.o -o libfirewall.so

main.o: string-array.h generic-string.h input.h string.h ip.h port.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

string-array.o: string-array.cpp string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c string-array.cpp

string.o: string.cpp string.h string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c string.cpp

ip.o: ip.cpp ip.h string.h string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c ip.cpp

port.o: port.cpp port.h string.h string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c port.cpp


clean:
	$(RM) $(OBJS) $(EXEC)