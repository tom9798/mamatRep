CXX=g++
CXXLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11 -fpic
OBJS=string.o ip.o port.o main.o string-array.o
#LIBS = -lfirewall -L. -linput -L.


firewall.exe:string-array.o string.o ip.o port.o main.o libfirewall.so libinput.so
	$(CXXLINK) $(OBJS) -o firewall.exe -firewall -linput -L.

main.o: main.cpp string-array.h generic-string.h input.h string.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ip.o: ip.cpp ip.h string.h string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c ip.cpp

port.o: port.cpp port.h string.h string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c port.cpp

string.o: string.cpp string.h string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c string.cpp

string-array.o: string-array.cpp string-array.h generic-string.h
	$(CXX) $(CXXFLAGS) -c string-array.cpp

libfirewall.so: string.o ip.o port.o string-array.o
	$(CXXLINK) -shared string.o ip.o port.o string-array.o -o libfirewall.so

clean:
	rm -rf $(OBJS) firewall.exe libfirewall.so