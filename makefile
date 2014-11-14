#include ../rule.mk

history: history.o gdeque.o cstring.o
	$(CXX) -o $@ $^ -lncursesw
#gdeque: gdeque.o
#	$(CXX) -o $@ $^
m: m.o mydeque.o
	$(CXX) -o $@ $^

main: main.o queue.o
	$(CXX) -o $@ $^

gdeque: gdeque.cpp gdeque.h
	$(CXX) -DOS_CPP -DTEST_GDEQUE -o $@ $^

gdeque.o: gdeque.cpp gdeque.h
	$(CXX) -DOS_CPP -c $<

cstring.o: cstring.cpp cstring.h
	$(CXX) -DOS_CPP -c $<

history.o: history.cpp 
	$(CXX) -DOS_CPP -c $<

#sources = queue.cpp main.cpp mydeque.cpp m.cpp gdeque.cpp history.cpp cstring.cpp
#include $(sources:.cpp=.dpp)

clean:
	rm -rf *.o
