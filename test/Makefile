
CXX= g++
CXXTESTGEN=cxxtestgen
CXXFLAGS= -g
INCLUDES += -I../src

LIBPATH= -L../lib 
LIBS= -lsearcher -lgcov
BINS= testrunner

.SUFFIXES: .cpp .ut

.ut.cpp:
	$(CXXTESTGEN) --error-printer -o $(TESTSRCS) $<

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBPATH) $(LIBS) -c $<

all: $(BINS) valgrind runtest

SRCS= searchtest.ut

TESTSRCS= $(addsuffix .cpp, $(basename $(SRCS)))

TESTOBJS= $(addsuffix .o, $(basename $(SRCS)))

testrunner: $(TESTSRCS) $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(TESTOBJS) $(LIBPATH) $(LIBS)

valgrind:
	valgrind --tool=memcheck --error-exitcode=1 --fullpath-after= --gen-suppressions=all --leak-check=full --num-callers=50 --show-leak-kinds=definite --errors-for-leak-kinds=definite $(BINS)

runtest:
	mkdir -p ../coverage
	lcov --directory ../src --zerocounters
	$(BINS)
	lcov --directory ../src  --rc lcov_branch_coverage=1 --capture --output-file ../coverage/stap.info
	genhtml --branch-coverage -o ../coverage ../coverage/stap.info

.PHONY: clean

clean:
	rm -rf $(BINS) $(TESTSRCS) $(TESTOBJS) *~
	rm -rf ../coverage
