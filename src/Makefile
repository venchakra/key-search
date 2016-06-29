
AR= ar
LN= ln
CXX= g++
CXXFLAGS= -g -fprofile-arcs -ftest-coverage
INCLUDES += -I./
LIBNAME=searcher
LIBA= lib$(LIBNAME).a

TESTPATH= ./test
#LIBS= -lsearcher
#BINS= searcher

.SUFFIXES: .cc

.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

all: $(LIBA)

SRCS=	search.cc

OBJS= $(addsuffix .o, $(basename $(SRCS)))

$(LIBA): $(OBJS)
	$(AR) -r $@ $(OBJS)
	mkdir -p ../lib
	rm -f ../lib/$@
	mv $@ ../lib/$@

.PHONY: clean

clean:
	rm -rf ../lib/$(LIBA) $(OBJS) *~ *.gc* *.html
	rm -rf ../lib
