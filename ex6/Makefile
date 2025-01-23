CXX=g++
CXXLINK=$(CXX)
CXXFLAGS= -g -Wall -std=c++11
OBJS= string.o ip.o port.o string-array.o
RM= rm -rf

firewall.exe: main.o libfirewall.so
	$(CXXLINK) $(CXXFLAGS) main.o -o firewall.exe -lfirewall -linput -L.

libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so

string.o: string.h string.cpp generic-string.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic string.cpp

string-array.o: string-array.h string-array.cpp string.h generic-string.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic string-array.cpp

ip.o: ip.h ip.cpp string.h string-array.h generic-field.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.h port.cpp string.h string-array.h generic-field.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic port.cpp

main.o: main.cpp string.h string-array.h ip.h port.h input.h generic-string.h generic-field.h
	$(CXXLINK) $(CXXFLAGS) -c -fpic main.cpp

clean:
	$(RM) *.o