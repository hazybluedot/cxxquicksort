CXXC := g++ 
CXXFLAGS := -Wall -g -std=c++11

all: testsort

testsort: testsort.o
	$(CXXC) -o $@ $^

testsort.o : testsort.cpp quicksort.h util.h
	$(CXXC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o 
