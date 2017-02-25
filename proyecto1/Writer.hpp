/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Tools for reading the file and creating the graph
 */


#ifndef WRITER_HPP_
#define WRITER_HPP_

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
using namespace std;


/**
 * Writes a feasible solution for PRPP into a file
 * @param file: name of the file to be written
 * @param path: the solution to PRPP.
 * @param benefit: benefit of the solution
 */

void writeFile(const char* file, std::pair < int,std::vector<int> > result){

	int benefit = result.first;
	std::vector<int> path = result.second;
	ofstream sourcefile; //File to be written
    sourcefile.open(file);
	//Make sure the file exists
	if(sourcefile.is_open()){

        sourcefile << benefit << std::endl;
        for(std::vector<int>::iterator vi = path.begin(); vi != path.end(); ++vi) {
            // std::cout << vi << std::endl;
			if (*vi == 1) {
				sourcefile << "d "; // Source vertex
			}
			else {
            	sourcefile << *vi << " ";
			}
        }
	}
	else { cout << "Unable to read specified file..." << endl; }
    sourcefile.close();
}

#endif // WRITER_HPP_
