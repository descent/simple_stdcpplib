include ../rule.mk

history: history.o gdeque.o cstring.o
	$(CXX) -o $@ $^ -lncursesw
gdeque: gdeque.o
	$(CXX) -o $@ $^
m: m.o mydeque.o
	$(CXX) -o $@ $^

main: main.o queue.o
	$(CXX) -o $@ $^

sources = queue.cpp main.cpp mydeque.cpp m.cpp gdeque.cpp history.cpp cstring.cpp
include $(sources:.cpp=.dpp)

clean:
	rm -rf *.o
