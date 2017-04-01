CXX = g++
OPT = -g -Wall -O3 -w -Wsign-compare -std=c++11

main: main.cpp
	$(CXX) $(OPT) main.cpp -o $@
	rm -f $*.c

runProject: runProject.cpp
	$(CXX) $(OPT) runProject.cpp -o $@
	rm -f $*.c

BranchAndBound: BranchAndBound.cpp
	$(CXX) $(OPT) BranchAndBound.cpp -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -f main runProject BranchAndBound *.o *~
