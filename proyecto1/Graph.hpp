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

#include <vector>
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

inline std::ostream& operator<<(std::ostream &os, Edge &edge) {
    edge.print(os);
    return os;
}

void printEdges(std::ostream &os, std::vector<Edge> &edges) {
    for(std::vector<Edge>::iterator it= edges.begin(); it != edges.end(); ++it) {
		it -> print(os);
	}
}

bool isConnected(int n_vertex, std::vector<Edge> edges) {

    // bool isDeposit = false; //Whether the source is in the graph
    std::set<int> visitedVertex; // Set for visited vertexes.
    int v1, v2;

    // Find first edge of source vertex
    for(std::vector<Edge>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
        v1 = edge -> get_v1();
        v2 = edge -> get_v2();
        visitedVertex.insert(v1);
        visitedVertex.insert(v2);

        // if (v1 == 1 || v2 == 1){
        //     isDeposit = true;
        // }
    }
    // for(std::set<int>::iterator v = visitedVertex.begin(); v != visitedVertex.end(); ++v){
    //     std::cout << "valor" << *v;
    // }
    // std::cout << visitedVertex.size() << std::endl;
    return visitedVertex.size() >= n_vertex;
}

/**
 *  Checks if an vector of edges is an eulerian cycle
 *  @param n_vertex: number of vertexes of the graph
 *  @param edges: vector of edges (graph) to be checked
 *  @return true/false
 */
bool isEulerian(int n_vertex, std::vector<Edge> edges) {

    int even [n_vertex]; // array to check whether a vertex has an even number of edges
    int v1, v2; // Edge

    // Initialize array of vertexes
    for (int i = 0; i < n_vertex; i++) {
        even[i] = 0;
    }
    for(std::vector<Edge>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        even[v1] = (even[v1] + 1) % 2;
        even[v2] = (even[v2] + 1) % 2;
    }

    for (int i = 0; i < n_vertex; i++) {
        if (even[i] == 1) { // A vertex does not have an even number of edges
            return false;
        }
    }
    return true;
}

/**************************************************************************//**
 *  Graph. vector of the edges and it's benefits and costs
 *****************************************************************************/
class Graph {
    private:
		int vertex;  //Number of vertex of the Graph
		int r_size; //Number of required edges of the Graph
		int n_size; //Number of non required edges of the Graph
        std::vector<Edge> r_edges; //List of required edges
        std::vector<Edge> n_edges; //List of non required edges

    public:
        Graph(int vertex, int r_size, int n_size, std::vector<Edge> &r_edges, std::vector<Edge> &n_edges);
        int get_vertex()  { return this -> vertex; }
        int get_r_size()  { return this -> r_size; }
        int get_n_size()  { return this -> n_size; }
        std::vector<Edge> get_r_edges() { return this -> r_edges; }
        std::vector<Edge> get_n_edges() { return this -> n_edges; }
        //FUNCIONES QUE PODRIA TENER, AUN NO ESTOY SEGURA
        void print(std::ostream &os);
        std::vector<Edge> MST();
        //void solvePRPP();
};

inline std::ostream& operator<<(std::ostream &os, Graph &graph) {
    graph.print(os);
    return os;
}

// Constructor
Graph::Graph (int vertex, int r_size, int n_size, std::vector<Edge> &r_edges, std::vector<Edge> &n_edges) {

	this -> vertex = vertex;
	this -> r_size = r_size;
	this -> n_size = n_size;
	this -> r_edges = r_edges;
	this -> n_edges = n_edges;
	//we proceed to sort the lists for easy work later
	// this -> r_edges.sort(comp);
	// this -> n_edges.sort(comp);
}

//Prints the current Graph Info
inline void Graph::print(std::ostream &os)  {

	os << "Number of vertex: " << this->vertex << endl;
	os << "Required edges: " << this->r_size << endl;
    printEdges(os, this -> r_edges);
	os << "Non Required edges: " << this->n_size << endl;
    printEdges(os, this -> n_edges);
}

//Creates the Maximun Spanning Tree (Variation Of Kruskall)
std::vector<Edge> Graph::MST(){

	// std::list<Edge> result; //Variable for the returning
	//YA LAS LISTAS ESTAN ORDENADAS DONDE POR BENEFICIO MAYOR A COSTO
	//NO SE SI DEJARLO ASI U ORDENARLOS POR BENEFICIO MAYOR A 2 VECES COSTO

    std::set<int> visitedVertex; // Set for visited vertex.
    int v1, v2;
    // Initialize visited vertexes
    for(std::vector<Edge>::iterator edge = this -> r_edges.begin(); edge != this -> r_edges.end(); ++edge) {
        v1 = edge -> get_v1();
        v2 = edge -> get_v2();
        visitedVertex.insert(v1);
        visitedVertex.insert(v2);
    }

    std::priority_queue<Edge, std::vector<Edge> > edges_queue;

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
