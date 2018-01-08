CXX = c++
CXXFLAGS = -Wall -Wextra -ansi -pedantic
CXXLIBS = -lcppunit

TESTOBJS = InfinitableTest.o testmain.o

all: test.bin

test.bin: $(TESTOBJS)
	$(CXX) -o $@ $(TESTOBJS) $(CXXLIBS)

InfinitableTest.o: InfinitableTest.cpp infinitable.h

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

test: test.bin
	./test.bin

clean:
	rm -f test.bin $(TESTOBJS)

.PHONY: all test clean