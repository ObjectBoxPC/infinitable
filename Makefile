CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -iquote .
CXXLIBS = -lcppunit

TESTTARGET = test/test.bin
TESTOBJS = test/InfinitableTest.o test/main.o
READMETESTTARGET = test/readme-test.bin
READMETESTOBJS = test/readme-test.gen.o
READMETESTSRC = test/readme-test.gen.cpp

all: $(TESTTARGET) $(READMETESTTARGET)

$(TESTTARGET): $(TESTOBJS)
	$(CXX) -o $@ $(TESTOBJS) $(CXXLIBS)

test/InfinitableTest.o: test/InfinitableTest.cpp infinitable.h

$(READMETESTTARGET): $(READMETESTOBJS)
	$(CXX) -o $@ $(READMETESTOBJS)

test/readme-test.o: $(READMETESTSRC) infinitable.h

$(READMETESTSRC): README.md
	awk '/^```/ { testsrc = !testsrc }; !/^```/ { if (testsrc) { print; } }' < README.md > $(READMETESTSRC)

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

test: $(TESTTARGET) $(READMETESTTARGET)
	./$(TESTTARGET)
	./$(READMETESTTARGET)

clean:
	rm -f $(TESTTARGET) $(TESTOBJS) $(READMETESTTARGET) $(READMETESTOBJS) $(READMETESTSRC)

.PHONY: all test clean