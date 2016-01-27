CXX=g++

CXXFLAGS=-m32 -Wall -O2 -nostdlib -nostartfiles -ffreestanding -fno-exceptions -fno-rtti 

all : start.o bios_call.o

start.o : start.s
	$(CXX) $(CXXFLAGS) -c $<

bios_call.o: bios_call.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean :
	rm -f *.o
