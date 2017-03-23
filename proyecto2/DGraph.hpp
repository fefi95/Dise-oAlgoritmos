/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Information of the graph
 */

#ifndef _DGRAPH_HPP
#define _DGRAPH_HPP

#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Union-find.hpp"

using namespace std;

/**************************************************************************//**
 *  Edge. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
class DEdge {
    private:
        int vIn;      // Incident vertex
        int be;      // Edge's benefit
        int ce;      // Edge's cost
        int times;

    public:
        DEdge(int, int, int);

        //Prints the current Edge Info
        void print(std::ostream &os);

        int get_vIn() { return this -> vIn; }
        int get_cost() {return this -> ce;}
        int get_benefit() {return this -> be;}
        int set_times(int t) {return this -> times = t;}
        int get_times() {return this -> times;}
        // bool operator< (const Edge &edge) const {
        //     return this -> crossE2 < edge.crossE2;
        // }
};

// Constructor
DEdge::DEdge (int vIn, int ce, int be) {
    this -> vIn = vIn;
    this -> be = be;
    this -> ce = ce;
    this -> times = 0;
}

inline void DEdge::print(std::ostream &os)  {

    os << "(vertex: " << this -> vIn + 1 << ", cost: " <<
	this->ce << ", benefit: "<< this -> be << " ) ";

}

//Aux function to specify the order to sort a list
//Does not form part of the namesapce Edge
bool comp (DEdge a, DEdge b) {

	return ((a.get_benefit() - a.get_cost()) > (b.get_benefit() - b.get_cost()));

}

inline std::ostream& operator<<(std::ostream &os, DEdge &edge) {
    edge.print(os);
    return os;
}

void printEdges(std::ostream &os, std::vector<DEdge> edges) {
    os << "[";
    for(std::vector<DEdge>::iterator it= edges.begin(); it != edges.end(); ++it) {
		it -> print(os);
	}
    os << "]" << endl;
}

/**************************************************************************//**
 *  Graph. vector of the edges and it's benefits and costs
 *****************************************************************************/
class DGraph {
    private:
		int n_vertex;  // Number of vertex of the Graph
        std::vector< vector<DEdge> > graph; //List with the whole graph

    public:
        DGraph(int n_vertex, vector< vector<DEdge> > graph);
        int get_n_vertex()   { return this -> n_vertex; }
        std::vector< vector<DEdge> > get_graph() { return this -> graph; }
        std::vector<DEdge> get_successor_list(int vOut);
        void print(std::ostream &os);
};

inline std::ostream& operator<<(std::ostream &os, DGraph &graph) {
    graph.print(os);
    return os;
}

// Constructor
DGraph::DGraph (int n_vertex, vector< vector<DEdge> > graph) {

	this -> n_vertex = n_vertex;
	this -> graph = graph;

    //we proceed to sort the lists for easy work later
    // for (int vi = 0; vi < this -> n_vertex; vi++) {
    //     std::sort(graph[vi].begin(), graph[vi].end(), comp);
    // }
}

std::vector<DEdge> DGraph::get_successor_list(int vOut){ //CAMBIAR
    // ORDENAR
    return this-> graph[vOut];
}

int DGraph::beneficio(){
    //inserte su codigo aqui
    return 0;
}
//Prints the current Graph Info
inline void DGraph::print(std::ostream &os)  {

    for (int vi = 0; vi < this -> n_vertex; vi++) {
        os << vi + 1 << " -> ";
        printEdges(os, this-> graph[vi]);
    }
}

#endif // _GRAPH_HPP
