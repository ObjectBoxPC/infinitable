CXX = g++
CXXFLAGS = -Wall -Wextra -ansi -pedantic
CXXLIBS = -lcppunit

OBJS = InfinitableTest.o testmain.o

all: test.bin

test.bin: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXLIBS)

InfinitableTest.o: InfinitableTest.cpp infinitable.h

testmain.o: testmain.cpp

test: test.bin
	./test.bin

clean:
	rm -f test.bin $(OBJS)

.PHONY: clean