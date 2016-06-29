# key-search

This code has been compiled using:
- g++ (version 4.8.4) -- the C++ compiler
- gcov (version 4.8.4) -- for code coverage
- lcov/genhtml (version 1.10) -- for code coverage and HTML reports
- cxxtestgen (version 4.3) -- for CxxTest automated unit tests

The above tools need to be installed on your system before building
the sources and executing the unit tests.

---------------------------------------------------------------------------
C++ Source Files
---------------------------------------------------------------------------
Source file containing the implementation of the Search API is at:
              mapr/src/search.cpp(.h)

---------------------------------------------------------------------------
CxxTest Automated Unit Tests
---------------------------------------------------------------------------
All automated CxxTest unit tests are located at:
              mapr/test/searchtest.ut

---------------------------------------------------------------------------
Makefile
---------------------------------------------------------------------------
A Makefile has been provided at
              mapr/Makefile
which will invoke
              mapr/src/Makefile
to build the source files and package it as a library and also invoke
              mapr/test/Makefile
to build the CxxTest unit tests, execute them and generate code coverage
reports.

In other words this Makefile will do the following:

   - Package the Search API implementation at
              mapr/src/search.cpp
     as a userspace library
              mapr/lib/libsearcher.a

   - Compile the unit tests (under
              mapr/test/searchtest.ut
     and build a test binary
              mapr/test/testrunner

   - Run the unit tests and generate a code coverage report for the
     source file. The HTML file containing the code coverage is
     located at
              mapr/coverage/index.html
     and
              mapr/coverage/src/search.cpp.gcov.html

   Opening the above HTML files in a browser: 
              file://localhost/<yourdir>/mapr/coverage/src/search.cpp.gcov.html
   will help you see the code coverage report

---------------------------------------------------------------------------
Example run: Running 'make clean'
---------------------------------------------------------------------------
venkatc@ubuntu-pc:/media/sf_Code/mapr $make clean
set -e; for d in src test; do make -C $d clean; done
make[1]: Entering directory `/media/sf_Code/mapr/src'
rm -rf ../lib/libsearcher.a search.o *~ *.gc* *.html
rm -rf ../lib
make[1]: Leaving directory `/media/sf_Code/mapr/src'
make[1]: Entering directory `/media/sf_Code/mapr/test'
rm -rf testrunner searchtest.cpp searchtest.o *~
rm -rf ../coverage
make[1]: Leaving directory `/media/sf_Code/mapr/test'
rm -rf *~

---------------------------------------------------------------------------
Example run: Running 'make'
---------------------------------------------------------------------------
venkatc@ubuntu-pc:/media/sf_Code/mapr $make
set -e; for d in src test; do make -C $d ; done
make[1]: Entering directory `/media/sf_Code/mapr/src'
g++ -g -fprofile-arcs -ftest-coverage   -c -o search.o search.cpp
ar -r libsearcher.a search.o
ar: creating libsearcher.a
mkdir -p ../lib
rm -f ../lib/libsearcher.a
mv libsearcher.a ../lib/libsearcher.a
make[1]: Leaving directory `/media/sf_Code/mapr/src'
make[1]: Entering directory `/media/sf_Code/mapr/test'
cxxtestgen --error-printer -o searchtest.cpp searchtest.ut
g++ -g -I../src -L../lib  -lsearcher -lgcov -c searchtest.cpp
g++ -g -I../src -o testrunner searchtest.o -L../lib  -lsearcher -lgcov
mkdir -p ../coverage
lcov --directory ../src --zerocounters
Deleting all .da files in ../src and subdirectories
Done.
testrunner
Running cxxtest tests (55 tests)
Dummy Test, does nothing
.
Search Ascending LessThan giving NotFound 0
.
Search Ascending LessThan giving FoundLess 0
.
Search Ascending LessThan giving NotFound 1
.
Search Ascending LessThan giving NotFound 2
.
Search Ascending LessThan giving FoundLess
.
Search Ascending LessThanEquals giving NotFound 0
.
Search Ascending LessThanEquals giving FoundExact 0
.
Search Ascending LessThanEquals giving FoundLess 0
.
Search Ascending LessThanEquals giving NotFound
.
Search Ascending LessThanEquals giving FoundExact
.
Search Ascending LessThanEquals giving FoundLess
.
Search Ascending Equals giving NotFound 0
.
Search Ascending Equals giving FoundExact 0
.
Search Ascending Equals giving FoundExact
.
Search Ascending Equals giving NotFound
.
Search Ascending GreaterThanEquals giving FoundGreater 0
.
Search Ascending GreaterThanEquals giving FoundExact 0
.
Search Ascending GreaterThanEquals giving NotFound 0
.
Search Ascending GreaterThanEquals giving FoundExact
.
Search Ascending GreaterThanEquals giving FoundGreater
.
Search Ascending GreaterThanEquals giving NotFound 1
.
Search Ascending GreaterThan giving FoundGreater 0
.
Search Ascending GreaterThan giving NotFound 0
.
Search Ascending GreaterThan giving FoundGreater
.
Search Ascending GreaterThan giving NotFound 1
.
Search Ascending GreaterThan giving NotFound 2
.
Search Ascending with Wrong Search Type
Error in search type
.
Search Ascending with NULL index pointer
.
Search Descending with Wrong Search Type
Error in search type
.
Search Descending LessThan giving FoundLess 0
.
Search Descending LessThan giving NotFound 0
.
Search Descending LessThan giving FoundLess
.
Search Descending LessThan giving NotFound 1
.
Search Descending LessThan giving NotFound 2
.
Search Descending LessThanEquals giving FoundLess 0
.
Search Descending LessThanEquals giving FoundExact 0
.
Search Descending LessThanEquals giving NotFound 0
.
Search Descending LessThanEquals giving FoundLess
.
Search Descending LessThanEquals giving FoundExact
.
Search Descending LessThanEquals giving NotFound
.
Search Descending Equals giving NotFound 0
.
Search Descending Equals giving NotFound 0
.
Search Descending Equals giving NotFound
.
Search Descending Equals giving FoundExact
.
Search Descending GreaterThanEquals giving NotFound 0
.
Search Descending GreaterThanEquals giving FoundExact 0
.
Search Descending GreaterThanEquals giving FoundGreater 0
.
Search Descending GreaterThanEquals giving NotFound
.
Search Descending GreaterThanEquals giving FoundExact
.
Search Descending GreaterThanEquals giving FoundGreater
.
Search Descending GreaterThan giving NotFound 0
.
Search Descending GreaterThan giving FoundGreater 0
.
Search Descending GreaterThan giving FoundGreater
.
Search Descending GreaterThan giving NotFound
.OK!
lcov --directory ../src  --rc lcov_branch_coverage=1 --capture --output-file ../coverage/stap.info
Capturing coverage data from ../src
Found gcov version: 4.8.4
Scanning ../src for .gcda files ...
Found 1 data files in ../src
Processing search.gcda
Finished .info-file creation
genhtml --branch-coverage -o ../coverage ../coverage/stap.info
Reading data file ../coverage/stap.info
Found 1 entries.
Found common filename prefix "/media/sf_Code/mapr"
Writing .css and .png files.
Generating output.
Processing file src/search.cpp
Writing directory view page.
Overall coverage rate:
  lines......: 100.0% (104 of 104 lines)
  functions..: 100.0% (8 of 8 functions)
  branches...: 96.3% (79 of 82 branches)
make[1]: Leaving directory `/media/sf_Code/mapr/test'
