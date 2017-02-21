/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo
 *  @author : Stefani Castellanos 11-11394
 *
 *  Implementation for a graphs respresenteed as a list of edges
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Reader.hpp"

using namespace std;

int main(int argc, char **argv) {
    Graph graph = readFile(argv[1]);
    std::cout << isEulerian(graph.get_vertex(), graph.get_r_edges()) << std::endl;
    // GraphPRPP.solvePRPP();
    std::cout << graph << std::endl;
}
