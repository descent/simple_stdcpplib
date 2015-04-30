# make TEST=1 will make mem for testing

CFLAGS += -g -std=c++11

ifdef TEST
CFLAGS += -DTEST
mem: mem.o
	g++ $(CFLAGS) -o $@ $<
endif
alloc: alloc.o mem.o
	g++ $(CFLAGS) -o $@ $^
alloc.o: alloc.cpp mem.h
	g++ $(CFLAGS) -c $<
mem.o: mem.cpp mem.h
	g++ $(CFLAGS) -c $<
clean:
	rm -rf *.o alloc
