CC=gcc
CXX=g++

btree: btree.o
	$(CXX) -o $@ $< 
btree.o: btree.cpp
	$(CXX) -c -g $<
clean:
	rm *.o
