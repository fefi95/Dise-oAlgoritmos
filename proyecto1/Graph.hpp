/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Information of the graph
 */

#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <list>
#include <iostream>
#include <set>
#include <queue>
#include <vector>

using namespace std;

/**************************************************************************//**
 *  Edge. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
class Edge {
    private:
        int v1, v2;  // Edge of the graph
        int be;      // Edge's benefit
        int ce;      // Edge's cost
        int crossE1; // Benefit of crossing an edge once
        int crossE2; // Benefit of crossing an edge twice

    public:
        Edge(int, int, int, int);

        //Prints the current Edge Info
        void print(std::ostream &os);

        int get_v1() { return this -> v1; }
        int get_v2() { return this -> v2; }

        int get_cost() {return this -> ce;}

        int get_benefit() {return this -> be;}

        bool operator< (const Edge &edge) const {
            return this -> crossE2 < edge.crossE2;
        }
};

// Constructor
Edge::Edge (int v1, int v2, int ce, int be) {
  this -> v1 = v1;
  this -> v2 = v2;
  this -> be = be;
  this -> ce = ce;
  this -> crossE1 = be - ce;
  this -> crossE2 = be - 2 * ce;
}

inline void Edge::print(std::ostream &os)  {

	os << "Start: " << this->v1 << " End: " << this->v2 << " Cost: " <<
	this->ce << " Benefit: "<< this->be << endl;

}

//Aux function to specify the order to sort a list
//Does not form part of the namesapce Edge
bool comp (Edge &a, Edge &b) {

	return ((a.get_benefit() - a.get_cost()) > (b.get_benefit() - b.get_cost()));

}

inline std::ostream& operator<<(std::ostream &os, Edge &Edge) {
    Edge.print(os);
    return os;
}

void printEdges(std::ostream &os, std::list<Edge> &edges) {
    for(std::list<Edge>::iterator it= edges.begin(); it != edges.end(); ++it) {
		it -> print(os);
	}
}

/**************************************************************************//**
 *  GraphPRPP. List of the edges and it's benefits and costs
 *****************************************************************************/
class GraphPRPP {
    private:
		int nodes;  //Number of nodes of the Graph
		int r_size; //Number of required edges of the Graph
		int n_size; //Number of non required edges of the Graph
        std::list<Edge> r_edges; //List of required edges
        std::list<Edge> n_edges; //List of non required edges
    public:
        GraphPRPP(int nodes, int r_size, int n_size, std::list<Edge> & r_edges, std::list<Edge> & n_edges);
        //FUNCIONES QUE PODRIA TENER, AUN NO ESTOY SEGURA
        void print(std::ostream &os) ;
        //void solvePRPP();
};

// Constructor
GraphPRPP::GraphPRPP (int nodes, int r_size, int n_size, std::list<Edge> & r_edges, std::list<Edge> & n_edges) {

	this -> nodes = nodes;
	this -> r_size = r_size;
	this -> n_size = n_size;
	this -> r_edges = r_edges;
	this -> n_edges = n_edges;
	//we proceed to sort the lists for easy work later
	this -> r_edges.sort(comp);
	this -> n_edges.sort(comp);
}

//Prints the current Graph Info
inline void GraphPRPP::print(std::ostream &os)  {

	os << "Number of Nodes: " << this->nodes << endl;
	os << "Required edges: " << this->r_size << endl;
    printEdges(os, this -> r_edges);
	os << "Non Required edges: " << this->n_size << endl;
    printEdges(os, this -> n_edges);
}

inline std::ostream& operator<<(std::ostream &os, GraphPRPP &graph) {
    graph.print(os);
    return os;
}

/**************************************************************************//**
 *  Graph. List of the edges and it's benefits and costs
 *****************************************************************************/
class Graph {
    private:
		int n_vertex;  //Number of nodes of the Graph
        std::list<Edge> edges; //List of edges

    public:
        Graph(int n_vertex, std::list<Edge> & edges);
        //FUNCIONES QUE PODRIA TENER, AUN NO ESTOY SEGURA
        void print(std::ostream &os);
        bool isEulerian();
        std::list<Edge> MST();
        //void solvePRPP();
};

bool Graph::isEulerian() {

    int aux [this -> n_vertex];

    for(std::list<Edge>::iterator edge = this -> edges.begin(); edge != this -> edges.end(); ++edge) {
        int v1 = edge -> get_v1();
        int v2 = edge -> get_v2();
        aux[v1] = (v1 + 1) % 2;
        aux[v2] = (v2 + 1) % 2;
    }

    for (int i = 0; i < this -> n_vertex; i++) {
        if (aux[i] != 0){
            return false;
        }
    }
    return true;
}

//Creates the Maximun Spanning Tree (Variation Of Kruskall)
std::list<Edge> Graph::MST(){

	// std::list<Edge> result; //Variable for the returning
	//YA LAS LISTAS ESTAN ORDENADAS DONDE POR BENEFICIO MAYOR A COSTO
	//NO SE SI DEJARLO ASI U ORDENARLOS POR BENEFICIO MAYOR A 2 VECES COSTO

    std::set<Edge> visitedVertex; // Set for visited nodes.
    std::priority_queue<Edge, std::vector<Edge> > q2; // priority_queue order by the cost of crossing twice

    //priority queue
    /*
    A = 0
    for each vertex v E G.v
        make-set(v)
    sort-edges
    for each edge
        if find-set(u) != find-set(v)
            A = A U {(u,v)}
            Union(u,v)
    return A
    */

}

#endif // _GRAPH_HPP
