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
	char * path = "/home/direnzo/Escritorio/Eclipse/Proyecto1/files/example";
    Graph graph = readFile(argv[1]);
    cout << "Grafo Original" << endl;
    cout << graph;
    cout << endl;

    std::pair < std::vector<Edge>,std::vector<Edge> > FinalGraph = graph.MST();
    std::vector<Edge> mst = FinalGraph.first;
    std::vector<Edge> nonmst = FinalGraph.second;

    cout << "GRAFO MST" << endl << endl;
    for (std::vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it){
    	cout << *it;
    }

    cout << endl;
    cout << "GRAFO EURELIANO" << endl;
    cout << endl;

    //We assume that mst can visit the whole graph nodes
    std::vector<Edge> eurelian = makeEurelian(graph.get_n_vertex(), mst, nonmst);
    for(std::vector<Edge>::iterator euIt = eurelian.begin(); euIt != eurelian.end(); ++euIt){
    	cout << *euIt;
    }


    // std::cout << "benefit=" << graph.get_path_benefit() << std::endl;

    // GraphPRPP.solvePRPP();
}
