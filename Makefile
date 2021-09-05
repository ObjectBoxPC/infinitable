CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic
CXXLIBS = -lcppunit

TESTTARGET = test/test.bin
TESTOBJS = test/InfinitableTest.o test/main.o

all: $(TESTTARGET)

$(TESTTARGET): $(TESTOBJS)
	$(CXX) -o $@ $(TESTOBJS) $(CXXLIBS)

test/InfinitableTest.o: test/InfinitableTest.cpp infinitable.h

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

test: $(TESTTARGET)
	./$(TESTTARGET)

clean:
	rm -f $(TESTTARGET) $(TESTOBJS)

.PHONY: all test clean