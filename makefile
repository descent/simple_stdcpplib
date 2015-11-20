CC=gcc
CXX=g++
bst: bst.o
	$(CXX) -o $@ $< 
bst.o: bst.cpp
	$(CXX) -c -g $<

btree: btree.o
	$(CXX) -o $@ $< 
btree.o: btree.cpp
	$(CXX) -c -g $<
clean:
	rm *.o
