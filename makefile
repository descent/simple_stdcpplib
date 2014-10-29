include ../rule.mk

m: m.o mydeque.o
	$(CXX) -o $@ $^

main: main.o queue.o
	$(CXX) -o $@ $^

sources = queue.cpp main.cpp mydeque.cpp m.cpp
include $(sources:.cpp=.dpp)

clean:
	rm -rf *.o
