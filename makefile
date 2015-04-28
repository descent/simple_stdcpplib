alloc: alloc.o mem.o
	g++ -o $@ $^
alloc.o: alloc.cpp
	g++ -c $<
mem.o: mem.cpp
	g++ -c $<
clean:
	rm -rf *.o alloc
