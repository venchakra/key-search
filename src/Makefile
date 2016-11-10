
AR= ar
LN= ln
CXX= g++
CXXFLAGS= -g -fprofile-arcs -ftest-coverage
CCCC= cccc
INCLUDES += -I./
LIBNAME=searcher
LIBA= lib$(LIBNAME).a

TESTPATH= ./test

.SUFFIXES: .cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: $(LIBA) cccc

SRCS=	search.cpp

OBJS= $(addsuffix .o, $(basename $(SRCS)))

$(LIBA): $(OBJS)
	$(AR) -r $@ $(OBJS)
	mkdir -p ../lib
	rm -f ../lib/$@
	mv $@ ../lib/$@

cccc:
	$(CCCC) $(SRCS)

.PHONY: clean

clean:
	rm -rf ../lib/$(LIBA) $(OBJS) *~ *.gc* *.html
	rm -rf ../lib
	rm -rf .cccc
