# make TEST=1 will make mem for testing

CFLAGS += -g

ifdef TEST
CFLAGS += -DTEST
mem: mem.o
	g++ $(CFLAGS) -o $@ $<
endif
alloc: alloc.o mem.o
	g++ -o $@ $^
alloc.o: alloc.cpp mem.h
	g++ -g -c $<
mem.o: mem.cpp mem.h
	g++ $(CFLAGS) -c $<
clean:
	rm -rf *.o alloc
