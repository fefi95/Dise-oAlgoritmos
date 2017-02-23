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
    // std::cout << "graph \n" << graph << std::endl;
    // std::cout << "isConnected: " << isConnected(graph.get_n_vertex(), graph.get_r2_edges()) << std::endl;
    std::cout << "isEulerian: " << graph.isEulerian() << std::endl;

    std::cout << "MST" << std::endl;
    std::vector<Edge> mst = graph.MST();
    for(std::vector<Edge>::iterator edge = mst.begin(); edge != mst.end(); ++edge) {
        edge -> print(std::cout);
    }
    std::cout << "eurelian" << std::endl;
    std::vector<Edge> eurelian = makeEurelian(mst.size(), mst, graph.get_r_edges());
    for(std::vector<Edge>::iterator edge = eurelian.begin(); edge != eurelian.end(); ++edge) {
        edge -> print(std::cout);
    }
    // std::cout << "benefit=" << graph.get_path_benefit() << std::endl;

    // GraphPRPP.solvePRPP();
}
