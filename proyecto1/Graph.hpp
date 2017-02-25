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
#include <vector>
#include <algorithm>
#include "Union-find.hpp"
#include "Writer.hpp"

using namespace std;

/**************************************************************************//**
 *  Edge. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
 class Edge {
     private:
         int v1, v2;  // Edge of the graph
         int be;      // Edge's benefit
         int ce;      // Edge's cost
         bool two_way; // Defines if the edge is a two way path

     public:
         Edge(int, int, int, int);

         //Prints the current Edge Info
         void print(std::ostream &os);

         int get_v1() { return this -> v1; }
         int get_v2() { return this -> v2; }
         int get_cost() {return this -> ce;}
         int get_benefit() {return this -> be;}
         bool is_two_way() {return (this->be > (2*(this->ce)));}
         void set_two_way() {this->two_way = true;}
         bool get_two_way() {return this->two_way;}
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
   this -> two_way  = false;
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

void printEdges(std::ostream &os, std::vector<Edge> edges) {
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
    for (int i = 0; i < n_vertex; ++i) {
        n_edges[i] = 0;
    }
    for(std::vector<Edge>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        ++n_edges[v1];
        ++n_edges[v2];
    }

    int count = 0;
    for (int i = 0; i < n_vertex; ++i) {
        if (n_edges[i] == 1) { // A vertex does not have an even number of edges
            ++count;
            if (count > 2) {
                return false;
            }
        }
    }
    return true;
}

std::pair < int,std::vector<int> > getPath(std::vector< vector<int> > path, std::vector<Edge> graph){

    for (int vi = 0; vi < path.size(); vi++) {
        for(std::vector<int>::iterator vj = path[vi].begin(); vj != path[vi].end(); ++vj) {
            std::cout << "(" << vi + 1 << " " << *vj + 1 << ")" << std::endl;
        }
    }
    int benefit = 0;
    std::vector<int> twice;
    bool flag = true;
    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
        if ( flag && ((edge -> get_v1() == 1) || (edge -> get_v2() == 1))) {
            flag = false;
            twice.push_back(1);
        }
        else {
            twice.push_back(0);
        }
    }

    std::vector<int> eulerian;
    for(std::vector<int>::iterator adj0 = path[0].begin(); adj0 != path[0].end(); ++adj0) {
        int u = 0;  //source
        eulerian.push_back(u + 1);
        std::cout << u + 1 << " ";
        int vi = *adj0;
        int getBack;
        while (vi != 0) {
            getBack = true;
            for (int j = 0; j < path[vi].size(); ++j) {
                int vj = path[vi][0];
                path[vi].erase(path[vi].begin());
                path[vi].push_back(vj);
                // std::cout << "d" << vj + 1 << std::endl;
                if (u != vj) {
                    // std::cout << "u" << std::endl;
                    // std::cout << vi + 1 << " " << vj + 1 << std::endl;
                    std::cout << vi + 1 << " ";
                    eulerian.push_back(vi + 1);
                    int pose = 0;
                    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
                        if ((edge -> get_v1() == vi+1 && edge -> get_v2() == vj+1) || (edge -> get_v1() == vj+1 && edge -> get_v2() == vi+1)) {
                            ++twice[pose];
                            // std::cout << "loco " << vi + 1 << " " << vj + 1 << "pos" << pose << std::endl;
                            break;
                        }
                        ++pose;
                    }
                    u = vi;
                    vi = vj;
                    getBack = false;
                    break;
                }
            }
            if (getBack) {
                // std::cout << vi + 1 << " " << u + 1 << std::endl;
                std::cout << vi + 1 << " ";
                eulerian.push_back(vi + 1);
                int pose = 0;
                for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
                    if ((edge -> get_v1() == vi+1 && edge -> get_v2() == u+1) || (edge -> get_v1() == u+1 && edge -> get_v2() == vi+1)) {
                        ++twice[pose];
                        // std::cout << "what? " << vi + 1 << " " << u + 1  << "pos" << pose << std::endl;
                        break;
                    }
                    ++pose;
                }
                vi = u;
            }
        }
    }

    eulerian.push_back(1);
    std::cout << 1 << std::endl;
    int i = 0;
    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
        benefit += edge -> get_benefit() - twice[i] * edge -> get_cost();
        // std::cout << twice[i] << " ";
        ++i;
    }
    std::cout << "b: " << benefit << std::endl;
    std::pair < int,std::vector<int> > result(benefit, eulerian);
    return result;
}

/**
 *  Add edges to a connected graph so it becames an eurelian cycle
 *  @param n_vertex: number of vertexes of the graph
 *  @param graph: vector of edges. Initial graph
 *  @param edges: vector of edges to be added to the graph
 *  @return true/false
 */

std::pair < int,std::vector<int> > makeEurelian(int n_vertex, std::vector<Edge> graph, std::vector<Edge> extras){

    int even [n_vertex]; // array to check whether a vertex has an even number of edges
    int v1, v2; // Edge
    // int benefit;

    // Initialize array of vertexes
    for (int i = 0; i < n_vertex; i++) {
        even[i] = 0;
    }

    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        even[v1] = (even[v1] + 1) % 2;
        even[v2] = (even[v2] + 1) % 2;
    }

    std::vector< vector<int> > path;
    for (int i = 0; i < n_vertex; i++) {
        std::vector<int> adjacent;
        path.push_back(adjacent);
    }

    std::vector<Edge> eulerian;
    int v1p, v2p;
    for(std::vector<Edge>::iterator edge = graph.begin(); edge != graph.end(); ++edge) {
        v1 = edge -> get_v1() - 1;
        v2 = edge -> get_v2() - 1;
        // if (even[v1] == 1 && even[v2] == 1) { // they are both odd vertices
        //     // std::cout << v1 << " both odd " << v2 << std::endl;
        //     if (edge -> get_benefit() - edge -> get_cost() > 0) { // It might be worth it to keep the edge that connects v1 and v2
        //         path[v1p].push_back(v2p);
        //         path[v2p].push_back(v1p);
        //         std::cout << "odd " << *edge << std::endl;
        //         eulerian.push_back(*edge);
        //     }
        //     else {
        //         even[v1] = 0;
        //         even[v2] = 0;
        //     }
        // }
        // else if (even[v1] == 1 && even[v2] == 0) { // v1 is odd
        //     // std::cout << v1 << " v1 odd " << v2 << std::endl;
        //     if (edge -> get_benefit() - edge -> get_cost() > 0) { // It might be worth it to keep the edge that connects v1 and v2
        //         for(std::vector<Edge>::iterator edgep = extras.begin(); edgep != extras.end(); ++edgep) {
        //             v1p = edgep -> get_v1() - 1;
        //             v2p = edgep -> get_v2() - 1;
        //             if (v1 == v1p || v1 == v2p) { // one of the edges leaving v1
        //                 bool isBetter = edgep -> get_benefit() - edgep -> get_cost() > - edge -> get_cost();
        //                 // std::cout << isBetter << std::endl;
        //                 if (isBetter) {
        //                     even[v1p] = (even[v1p] + 1) % 2;
        //                     even[v2p] = (even[v2p] + 1) % 2;
        //                     path[v1p].push_back(v2p);
        //                     path[v2p].push_back(v1p);
        //                     std::cout << "pair v2"<< *edgep << std::endl;
        //                     eulerian.push_back(*edgep);
        //                 }
        //                 break;
        //             }
        //         }
        //         path[v1].push_back(v2);
        //         path[v2].push_back(v1);
        //         std::cout << "pair v2"<< *edge << std::endl;
        //         eulerian.push_back(*edge);
        //     }
        // }
        // else if (even[v1] == 0 && even[v2] == 1) { // v2 is odd
        //     // std::cout << v1 << " v2 odd " << v2 << std::endl;
        //     if (edge -> get_benefit() - edge -> get_cost() > 0) {
        //         for(std::vector<Edge>::iterator edgep = extras.begin(); edgep != extras.end(); ++edgep) {
        //             v1p = edgep -> get_v1() - 1;
        //             v2p = edgep -> get_v2() - 1;
        //             if (v2 == v1p || v2 == v2p) { // one of the edges leaving v2
        //                 bool isBetter = edgep -> get_benefit() - edgep -> get_cost() > - edge -> get_cost();
        //                 // std::cout << isBetter << std::endl;
        //                 if (isBetter) {
        //                     even[v1p] = (even[v1p] + 1) % 2;
        //                     even[v2p] = (even[v2p] + 1) % 2;
        //                     path[v1p].push_back(v2p);
        //                     path[v2p].push_back(v1p);
        //                     std::cout << "pair v1 " << *edge << std::endl;
        //                     std::cout << *edgep << std::endl;
        //                     eulerian.push_back(*edgep);
        //                 }
        //                 break;
        //             }
        //         }
        //         path[v1].push_back(v2);
        //         path[v2].push_back(v1);
        //         std::cout << "pair v1 " << *edge << std::endl;
        //         eulerian.push_back(*edge);
        //     }
        // }
        // else {
            path[v1].push_back(v2);
            path[v2].push_back(v1);
            std::cout << "pair " <<*edge << std::endl;
            eulerian.push_back(*edge);
        // }
    }
    return getPath(path, eulerian);
}

/**************************************************************************//**
 *  Graph. vector of the edges and it's benefits and costs
 *****************************************************************************/
class Graph {
    private:
		int n_vertex;  // Number of vertex of the Graph
        int r2_size;  // Number of edges that get benefit after crossing them twice
		int r_size;   // Number of required that get benefit after crossing them once
		int n_size;   // Number of non required edges of the Graph
		std::vector<Edge> r2_edges; //List of required edges that get benefit after crossing them twice
        std::vector<Edge> r_edges; //List of required edges
        std::vector<Edge> n_edges; //List of non required edges

    public:
        Graph(int n_vertex, int r2_size, int r_size, int n_size,std::vector<Edge> &r2_edges, std::vector<Edge> &r_edges, std::vector<Edge> &n_edges);
        int get_n_vertex()   { return this -> n_vertex; }
        int get_r2_size()  { return this -> r2_size; }
        int get_r_size()   { return this -> r_size; }
        int get_n_size()   { return this -> n_size; }
        std::vector<Edge> get_r2_edges() { return this -> r2_edges; }
        std::vector<Edge> get_r_edges()  { return this -> r_edges; }
        std::vector<Edge> get_n_edges()  { return this -> n_edges; }

        void print(std::ostream &os);

        bool isEulerian();
        std::pair < std::vector<Edge>,std::vector<Edge> > MST();
        void improveSolution();
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
	os << "Required edges: " << this-> r2_size + r_size << endl;
    printEdges(os, this -> r2_edges);
    printEdges(os, this -> r_edges);
	os << "Non Required edges: " << this->n_size << endl;
    printEdges(os, this -> n_edges);
}

/**
 *  Checks if an vector of edges is an eulerian cycle
 *  @param n_vertex: number of vertexes of the graph
 *  @param edges: vector of edges (graph) to be checked
 *  @return true/false
 */
bool Graph::isEulerian() {

    int even [n_vertex]; // array to check whether a vertex has an even number of edges
    int v1, v2; // Edge

    // Initialize array of vertexes
    for (int i = 0; i < n_vertex; i++) {
        even[i] = 0;
    }
    for(std::vector<Edge>::iterator edge = r_edges.begin(); edge != r_edges.end(); ++edge) {
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
 * Creates the Minimum Spanning Tree (Variation Of Kruskall) for non-required
 * edges connecting isolated connected components
 */
std::pair < std::vector<Edge>,std::vector<Edge> > Graph::MST(){

	std::vector<Edge> mst; // MST for the original graph
	std::vector<Edge> nonMst; // Edges that are not in the MST
    Edge edge(0,0,0,0);
    int v1, v2; // Vertexes that belong to an edge
    Union_find uf(n_vertex); // Disjoint set

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

        else {
        	nonMst.push_back(*edge);
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

            else {
            	nonMst.push_back(*edge);
            }
        }
    }
    std::pair < std::vector<Edge>,std::vector<Edge> > Edges(mst,nonMst);
    return Edges;
}

void Graph::improveSolution(){

    //
    // foreach par de lados duplicados e1 = (i;j)y e2 = (i;j) enGsol do
    //     G2sol Eliminar los ladose1 y e2 de Gsol
    //     if G2 sol es un grafo euleriano con mayor beneficio then
    //     //G 0 sol es conexo y todos sus vertices tienen grado par
    //         Gsol G2sol
    //         C Obtener un ciclo euleriano de Gsol

    // Parte 2: Eliminacion de Componente Conexa foreachpar de lados duplicados e1= (i;j)ye2= (i;j) enGsol
    // do G 0 solEliminar los lados e1 y e2 de Gsol
    //     if G 0 sol es un grafo desconectado then
    //         Gcc Se crea un grafo con la componente conexa de G2sol que contiene al deposito
    //         Ccc obtener un ciclo euleriano de Gcc
    //         if beneficio(Ccc)>beneficio(C) then
    //             C Ccc
    //             Gsol Gcc
    // return C
}

std::vector<Edge> Graph::solvePRPP(){

	std::vector<Edge> solution;

    if (this -> isEulerian()){
        return this -> r_edges;
    }
    else {
        //std::vector<Edge> mst = this -> MST();
        // solution = makeEurelian(..., mst);
    }
    return solution;
}


#endif // _GRAPH_HPP
