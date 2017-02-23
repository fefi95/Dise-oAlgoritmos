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

void writeFile(const char* file, std::vector< vector<int> > path, int benefit){

	ofstream sourcefile; //File to be written
    sourcefile.open(file);
	//Make sure the file exists
	if(sourcefile.is_open()){

        sourcefile << benefit << std::endl;
        sourcefile << "d "; // Source vertex
        int vi = path[0][0];
        while (vi != 1){
            std::cout << vi << std::endl;
            sourcefile << vi << " ";
            vi = path[vi - 1][0];
            path[vi - 1].erase (path[vi - 1].begin());
        }
        sourcefile << "d" << std::endl; // Source vertex
	}
	else { cout << "Unable to read specified file..." << endl; }
    sourcefile.close();
}

#endif // WRITER_HPP_
