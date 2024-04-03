CXX=g++ 
CXXFLAGS=-std=c++20 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS=${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=watopoly
DD1FILES = $(wildcard *.txt *.out *.in *.err *.ret)
DD2FILES = $(wildcard *.cc *.h Makefile)
TESTARGS = -v
SUITE = suite.txt
PROVIDED = ../execs/a4q3-provided

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include ${DEPENDS}

.PHONY: clean outs test

outs:
	produceOutputs $(SUITE) $(PROVIDED)

test: 
	make $(EXEC)
	runSuite $(TESTARGS) $(SUITE) ./$(EXEC)

sub-test:
	zip $(DD1ZIP) $(DD1FILES)
	marmoset_submit cs246 $(DD1TGT) $(DD1ZIP)

submit:
	zip $(DD2ZIP) $(DD2FILES)
	marmoset_submit cs246 $(DD2TGT) $(DD2ZIP)
	
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
