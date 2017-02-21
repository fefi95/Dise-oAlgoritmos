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
using namespace std;

/**************************************************************************//**
 *  GraphInfo. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
class GraphInfo {
    private:
        int v1, v2;  // Edge of the graph
        int be;      // Edge's benefit
        int ce;      // Edge's cost
        int crossE1; // Benefit of crossing an edge once
        int crossE2; // Benefit of crossing an edge twice

    public:
        GraphInfo(int, int, int, int);

        //Prints the current Edge Info
        void print();

        int get_cost() {return this -> ce;}

        int get_benefit() {return this -> be;}

};

// Constructor
GraphInfo::GraphInfo (int v1, int v2, int ce, int be) {
  this -> v1 = v1;
  this -> v2 = v2;
  this -> be = be;
  this -> ce = ce;
  this -> crossE1 = be - ce;
  this -> crossE2 = be - 2 * ce;
}

void GraphInfo::print(){

	cout << "Start: " << this->v1 << " End: " << this->v2 << " Cost: " <<
	this->ce << " Benefit: "<< this->be << endl;

}

//Aux function to specify the order to sort a list
//Does not form part of the namesapce GraphInfo
bool comp (GraphInfo &a, GraphInfo &b) {

	return ((a.get_benefit() - a.get_cost()) > (b.get_benefit() - b.get_cost()));

}



/**************************************************************************//**
 *  Graph. List of the edges and it's benefits and costs
 *****************************************************************************/
class Graph {
    private:
		int nodes;  //Number of nodes of the Graph
		int r_size; //Number of required edges of the Graph
		int n_size; //Number of non required edges of the Graph
        std::list<GraphInfo> r_edges; //List of required edges
        std::list<GraphInfo> n_edges; //List of non required edges
    public:
        Graph(int nodes, int r_size, int n_size, std::list<GraphInfo> & r_edges, std::list<GraphInfo> & n_edges);
        //FUNCIONES QUE PODRIA TENER, AUN NO ESTOY SEGURA
        void print();
        std::list<GraphInfo> MST();
        void isEulerian();
        void isConnected();
        void connectedComponents();
        //void solvePRPP();
};

// Constructor
Graph::Graph (int nodes, int r_size, int n_size, std::list<GraphInfo> & r_edges, std::list<GraphInfo> & n_edges) {

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
void Graph::print(){

	cout << "Number of Nodes: " << this->nodes << endl;
	cout << "Required edges: " << this->r_size << endl;
	for(std::list<GraphInfo>::iterator it= this->r_edges.begin(); it != this->r_edges.end();++it){

		it -> print();

	}
	cout << "Non Required edges: " << this->n_size << endl;
	for(std::list<GraphInfo>::iterator it= this->n_edges.begin(); it != this->n_edges.end();++it){

		it -> print();

	}
}

// inline std::ostream& operator<<(std::ostream &os, const Graph &graph) {
//     graph.print(os);
//     return os;
// }

//Creates the Maximun Spanning Tree (Variation Of Kruskall)
std::list<GraphInfo> Graph::MST(){

		// std::list<GraphInfo> result; //Variable for the returning
		// int visited_nodes[this->nodes] = {0}; //Array for the control of the visited nodes

		//YA LAS LISTAS ESTAN ORDENADAS DONDE POR BENEFICIO MAYOR A COSTO
		//NO SE SI DEJARLO ASI U ORDENARLOS POR BENEFICIO MAYOR A 2 VECES COSTO



}

#endif // _GRAPH_HPP
