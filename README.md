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
              src/search.cpp(.h)

---------------------------------------------------------------------------
CxxTest Automated Unit Tests
---------------------------------------------------------------------------
All automated CxxTest unit tests are located at:
              test/searchtest.ut

---------------------------------------------------------------------------
Makefile
---------------------------------------------------------------------------
A Makefile has been provided at
              Makefile
which will invoke
              src/Makefile
to build the source files and package it as a library and also invoke
              test/Makefile
to build the CxxTest unit tests, execute them and generate code coverage
reports.

In other words this Makefile will do the following:

   - Package the Search API implementation at
              src/search.cpp
     as a userspace library
              lib/libsearcher.a

   - It will run cccc which computes the cyclomatic complexity

   - Compile the unit tests (under
              test/searchtest.ut
     and build a test binary
              test/testrunner

   - Run the unit tests and generate a code coverage report for the
     source file. The HTML file containing the code coverage is
     located at
              coverage/index.html
     and
              coverage/src/search.cpp.gcov.html

   - It will also run Valgrind to check for any memory leaks

   Opening the above HTML files in a browser: 
              file://localhost/<yourdir>/coverage/src/search.cpp.gcov.html
   will help you see the code coverage report

---------------------------------------------------------------------------
Example run: Running 'make clean'
---------------------------------------------------------------------------
<pre>
venkatc@ubuntu-pc:/media/sf_Code/Algos $make clean
set -e; for d in src test; do make -C $d clean; done
make[1]: Entering directory `/media/sf_Code/Algos/src'
rm -rf ../lib/libsearcher.a search.o *~ *.gc* *.html
rm -rf ../lib
rm -rf .cccc
make[1]: Leaving directory `/media/sf_Code/Algos/src'
make[1]: Entering directory `/media/sf_Code/Algos/test'
rm -rf testrunner searchtest.cpp searchtest.o *~
rm -rf ../coverage
make[1]: Leaving directory `/media/sf_Code/Algos/test'
rm -rf *~
</pre>

---------------------------------------------------------------------------
Example run: Running 'make'
---------------------------------------------------------------------------
<pre>
venkatc@ubuntu-pc:/media/sf_Code/Algos $make
set -e; for d in src test; do make -C $d ; done
make[1]: Entering directory `/media/sf_Code/Algos/src'
g++ -g -fprofile-arcs -ftest-coverage -I./ -c search.cpp
ar -r libsearcher.a search.o
ar: creating libsearcher.a
mkdir -p ../lib
rm -f ../lib/libsearcher.a
mv libsearcher.a ../lib/libsearcher.a
cccc search.cpp
search.cpp
CCCC - a code counter for C and C++
===================================

A program to analyse C and C++ source code and report on
some simple software metrics
Version 3.1.4
Copyright Tim Littlefair, 1995, 1996, 1997, 1998, 1999, 2000
with contributions from Bill McLean, Herman Hueni, Lynn Wilson 
Peter Bell, Thomas Hieber and Kenneth H. Cox.

The development of this program was heavily dependent on
the Purdue Compiler Construction Tool Set (PCCTS) 
by Terence Parr, Will Cohen, Hank Dietz, Russel Quoung,
Tom Moog and others.

CCCC comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions.  See the file COPYING in the source
code distribution for details.
Parsing
Processing search.cpp as C/C++ (c++.ansi)

Generating HTML reports

Generating XML reports

Primary HTML output is in .cccc/cccc.html
Detailed HTML reports on modules and source are in .cccc
Primary XML output is in .cccc/cccc.xml
Detailed XML reports on modules are in .cccc
Database dump is in .cccc/cccc.db

make[1]: Leaving directory `/media/sf_Code/Algos/src'
make[1]: Entering directory `/media/sf_Code/Algos/test'
cxxtestgen --error-printer -o searchtest.cpp searchtest.ut
g++ -g -I../src -L../lib  -lsearcher -lgcov -c searchtest.cpp
g++ -g -I../src -o testrunner searchtest.o -L../lib  -lsearcher -lgcov
valgrind --tool=memcheck --error-exitcode=1 --fullpath-after= --gen-suppressions=all --leak-check=full --num-callers=50 --show-leak-kinds=definite --errors-for-leak-kinds=definite testrunner
==5208== Memcheck, a memory error detector
==5208== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==5208== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==5208== Command: testrunner
==5208== 
Running cxxtest tests (54 tests)
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
.
Search Descending with Wrong Search Type
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
==5208== 
==5208== HEAP SUMMARY:
==5208==     in use at exit: 0 bytes in 0 blocks
==5208==   total heap usage: 3 allocs, 3 frees, 880 bytes allocated
==5208== 
==5208== All heap blocks were freed -- no leaks are possible
==5208== 
==5208== For counts of detected and suppressed errors, rerun with: -v
==5208== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
mkdir -p ../coverage
lcov --directory ../src --zerocounters
Deleting all .da files in ../src and subdirectories
Done.
testrunner
Running cxxtest tests (54 tests)
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
.
Search Descending with Wrong Search Type
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
Found common filename prefix "/media/sf_Code/Algos"
Writing .css and .png files.
Generating output.
Processing file src/search.cpp
Writing directory view page.
Overall coverage rate:
  lines......: 100.0% (27 of 27 lines)
  functions..: 100.0% (2 of 2 functions)
  branches...: 100.0% (28 of 28 branches)
make[1]: Leaving directory `/media/sf_Code/Algos/test'
</pre>