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
#include "Writer.hpp"

using namespace std;

int main(int argc, char **argv) {
    DGraph graph = readFile2(argv[1]);
    cout << "Grafo Original" << endl;
    cout << graph << endl;
    std::vector<DEdge> s = graph.get_successor_list(0);
    printEdges(cout, s);

    // std::cout << "isEulerian: " << graph.isEulerian() << std::endl;
    //
    //
    // std::pair < std::vector<Edge>,std::vector<Edge> > FinalGraph = graph.MST();
    // std::vector<Edge> mst = FinalGraph.first;
    // std::vector<Edge> nonmst = FinalGraph.second;
    //
    // cout << "GRAFO MST" << endl << endl;
    // for (std::vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it){
    // 	cout << *it;
    // }
    //
    // cout << endl;
    // cout << "GRAFO EURELIANO" << endl;
    // cout << endl;
    //
    // //We assume that mst can visit the whole graph nodes
    // std::pair < int,std::vector<int> > result = makeEurelian(graph.get_n_vertex(), mst, nonmst);
    // // for(std::vector<Edge>::iterator euIt = eurelian.begin(); euIt != eurelian.end(); ++euIt){
    // //     std::cout << euIt -> get_two_way();
    // // 	cout << *euIt;
    // // }
    //
    // // test solution
    // // int one[] = {2};
    // // int two[] = {5, 1};
    // // int three[] = {2};
    // // int four[] = {3};
    // // int five[] = {4};
    // // std::vector< vector<int> > path;
    // // std::vector<int> tOne (one, one + sizeof(one) / sizeof(int) );
    // // std::vector<int> tTwo (two, two + sizeof(two) / sizeof(int) );
    // // std::vector<int> tThree (three, three + sizeof(three) / sizeof(int) );
    // // std::vector<int> tFour (four, four + sizeof(four) / sizeof(int) );
    // // std::vector<int> tFive (five, five + sizeof(five) / sizeof(int) );
    // // path.push_back(tOne);
    // // path.push_back(tTwo);
    // // path.push_back(tThree);
    // // path.push_back(tFour);
    // // path.push_back(tFive);
    // //
    // writeFile(strcat(argv[1], "-salida.txt"), result);
    // // std::cout << "benefit=" << graph.get_path_benefit() << std::endl;
    //
    // // GraphPRPP.solvePRPP();
}
