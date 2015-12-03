CC=gcc
CXX=g++
CXXFLAGS=-Wall -DTEST_MAIN -DUSE_OS
bst: bst.o
	$(CXX) $(CXXFLAGS) -o $@ $< 
bst.o: bst.cpp
	$(CXX) $(CXXFLAGS) -c -g $<

btree: btree.o
	$(CXX) -o $@ $< 
btree.o: btree.cpp
	$(CXX) -c -g $<
clean:
	rm *.o
