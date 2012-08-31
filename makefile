include ../rule.mk

main: main.o queue.o
	$(CXX) -o $@ $^
sources = queue.cpp main.cpp
include $(sources:.cpp=.dpp)

clean:
	rm -rf *.o
