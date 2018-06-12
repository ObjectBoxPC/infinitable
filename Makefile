CXXFLAGS = -Wall -Wextra -ansi -pedantic
CXXLIBS = -lcppunit

TESTTARGET = test.bin
TESTOBJS = InfinitableTest.o testmain.o

all: $(TESTTARGET)

$(TESTTARGET): $(TESTOBJS)
	$(CXX) -o $@ $(TESTOBJS) $(CXXLIBS)

InfinitableTest.o: InfinitableTest.cpp infinitable.h

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

test: $(TESTTARGET)
	./$(TESTTARGET)

clean:
	rm -f $(TESTTARGET) $(TESTOBJS)

.PHONY: all test clean