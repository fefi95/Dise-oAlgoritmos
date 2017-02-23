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
#include <algorithm>
#include "Union-find.hpp"

using namespace std;

/**************************************************************************//**
 *  Edge. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
class Edge {
    private:
        int v1, v2;  // Edge of the graph
        int be;      // Edge's benefit
        int ce;      // Edge's cost
        bool repeat; // Defines if the edge is a two way path

    public:
        Edge(int, int, int, int);

        //Prints the current Edge Info
        void print(std::ostream &os);

        int get_v1() { return this -> v1; }
        int get_v2() { return this -> v2; }
        int get_cost() {return this -> ce;}
        int get_benefit() {return this -> be;}
        void set_repeat() {this->repeat = true;}
        // bool operator< (const Edge &edge) const {
        //     return this -> crossE2 < edge.crossE2;
        // }
};

// Constructor
Edge::Edge (int v1, int v2, int ce, int be) {
  this -> v1 = v1;
  this -> v2 = v2;
  this -> be = be;
  this -> ce = ce;
  this -> repeat  = false;
}

inline void Edge::print(std::ostream &os)  {

	os << "Start: " << this->v1 << " End: " << this->v2 << " Cost: " <<
	this->ce << " Benefit: "<< this->be << endl;

}

//Aux function to specify the order to sort a list
//Does not form part of the namesapce Edge
bool comp (Edge a, Edge b) {

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

/**
 *  Checks if an vector of edges is connected. Any connected graph
 *  has at most 2 vertexes with only one edge incident.
 *  @param n_vertex: number of vertexes of the graph
 *  @param edges: vector of edges (graph) to be checked
 *  @return true/false
 */
bool isConnected(int n_vertex, std::vector<Edge> edges) {
    int n_edges [n_vertex]; // array for the number of edges incident in every node
    int v1, v2; // Edge

    // Initialize array of vertexes
    for (int i = 0; i < n_vertex; i++) {
        n_edges[i] = 0;
    }

    for(std::vector<Edge>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        ++n_edges[v1];
        ++n_edges[v2];
    }

    int count = 0;
    for (int i = 0; i < n_vertex; i++) {
        if (n_edges[i] == 1) { // A vertex does not have an even number of edges
            ++count;
            if (count > 2){
                return false;
            }
        }
    }
    return true;
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

/**
 *  Add edges to a connected graph so it becames an eurelian cycle
 *  @param n_vertex: number of vertexes of the graph
 *  @param graph: vector of edges. Initial graph
 *  @param edges: vector of edges to be added to the graph
 *  @return true/false
 */

std::vector<Edge> makeEurelian(int n_vertex, std::vector<Edge> graph, std::vector<Edge> edges){

    std::vector<Edge> eurelian;
    int even [n_vertex]; // array to check if a vertex is already an origin
    int v1, v2; // Edge

    // Initialize array of vertexes
    for (int i = 0; i < n_vertex; i++) {
        even[i] = 0;
    }

    //we must sort the edges to obtain the less cost's edge
    //std::sort(edges.begin(),edges.end(),comp);

    //we make sure to include all the initial graph to the eurelian answer
    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        even[v1] = (even[v1]+1)%2;
        even[v2] = (even[v2]+1)%2;
        eurelian.push_back(*edge);
    }
    //We study each edge to make sure ever vertex is even
    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge){
    	v1 = edge -> get_v1() - 1;
    	v2 = edge -> get_v2() - 1;
    	bool found = false;
    	std::vector<Edge>::iterator it;
    	if (even[v1] != 0) {
    		it = edges.begin();
    		//we try to find the best edge
    		while((!found) || (it != edges.end())){

    			found = ((v1+1) == it->get_v1());
    			if (found && (even[it->get_v2()-1] != 0)) {
    				even[it->get_v1()-1] = (even[it->get_v1()-1]+1)%2;
    				even[it->get_v2()-1] = (even[it->get_v2()-1]+1)%2;
    				eurelian.push_back(*it);
    			}
    			++it;
    		}
    		//If there is no path, we set a double path edge (a -> b and b -> a)
    		if (!found){
    			it->set_repeat();
    		}
    	}
    }


    return eurelian;
}

/**************************************************************************//**
 *  Graph. vector of the edges and it's benefits and costs
 *****************************************************************************/
class Graph {
    private:
		int n_vertex;  // Number of vertex of the Graph
        int r2_size; // Number of edges that get benefit after crossing them twice
		int r_size;  // Number of required that get benefit after crossing them once
		int n_size;  // Number of non required edges of the Graph
		std::vector<Edge> r2_edges; //List of required edges that get benefit after crossing them twice
        std::vector<Edge> r_edges; //List of required edges
        std::vector<Edge> n_edges; //List of non required edges

    public:
        Graph(int vertex, int r2_size, int r_size, int n_size,std::vector<Edge> &r2_edges, std::vector<Edge> &r_edges, std::vector<Edge> &n_edges);
        int get_n_vertex()   { return this -> n_vertex; }
        int get_r2_size()  { return this -> r_size; }
        int get_r_size()   { return this -> r_size; }
        int get_n_size()   { return this -> n_size; }
        std::vector<Edge> get_r2_edges() { return this -> r2_edges; }
        std::vector<Edge> get_r_edges()  { return this -> r_edges; }
        std::vector<Edge> get_n_edges()  { return this -> n_edges; }
        //FUNCIONES QUE PODRIA TENER, AUN NO ESTOY SEGURA
        void print(std::ostream &os);
        std::vector<Edge> MST();
        std::vector<Edge> solvePRPP();
};

inline std::ostream& operator<<(std::ostream &os, Graph &graph) {
    graph.print(os);
    return os;
}

// Constructor
Graph::Graph (int n_vertex, int r2_size, int r_size, int n_size, std::vector<Edge> &r2_edges, std::vector<Edge> &r_edges, std::vector<Edge> &n_edges) {

	this -> n_vertex = n_vertex;
    this -> r2_size = r2_size;
	this -> r_size = r_size;
	this -> n_size = n_size;
	this -> r2_edges = r2_edges;
	this -> r_edges = r_edges;
	this -> n_edges = n_edges;
    //we proceed to sort the lists for easy work later
	std::sort (this -> r_edges.begin(), this -> r_edges.end(), comp);
	std::sort (this -> n_edges.begin(), this -> n_edges.end(), comp);
}

//Prints the current Graph Info
inline void Graph::print(std::ostream &os)  {

	os << "Number of vertex: " << this->n_vertex << endl;
	os << "Required edges: " << this->r_size << endl;
    printEdges(os, this -> r_edges);
	os << "Non Required edges: " << this->n_size << endl;
    printEdges(os, this -> n_edges);
}

/**
 * Creates the Minimum Spanning Tree (Variation Of Kruskall) for non-required
 * edges connecting isolated connected components
 */
std::vector<Edge> Graph::MST(){

	std::vector<Edge> mst; //Variable for the returning
    Edge edge(0,0,0,0);
    int v1, v2;
    Union_find uf(n_vertex);

    // connected components
    for(std::vector<Edge>::iterator edge = this -> r2_edges.begin(); edge != this -> r2_edges.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        if(!uf.connected(v1, v2)){
            uf.set_union(v1, v2);
        }
        mst.push_back(*edge);
    }

    for(std::vector<Edge>::iterator edge = this -> r_edges.begin(); edge != this -> r_edges.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        if(!uf.connected(v1, v2)) {
            mst.push_back(*edge);
            uf.set_union(v1, v2);
        }
    }
    // All vertexes belong to the same tree
    if (uf.count() > 1) {
        for(std::vector<Edge>::iterator edge = this -> n_edges.begin(); edge != this -> n_edges.end(); ++edge) {
            v1 = edge -> get_v1() - 1;
            v2 = edge -> get_v2() - 1;
            if(!uf.connected(v1, v2)) {
                mst.push_back(*edge);
                uf.set_union(v1, v2);
            }
        }
    }
    return mst;
}

std::vector<Edge> Graph::solvePRPP(){

	std::vector<Edge> solution;

    if (isConnected(this -> n_vertex, this -> r2_edges)){
        //solution = r2_edges;
    }
    else if (isEulerian(this -> n_vertex, this -> r_edges)){
        return this -> r_edges;
    }
    else {
        //std::vector<Edge> mst = this -> MST();
        // solution = makeEurelian(..., mst);
    }
    return solution;
}


#endif // _GRAPH_HPP
