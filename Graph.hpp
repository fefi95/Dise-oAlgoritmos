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

/**************************************************************************//**
 *  GraphInfo. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
class GraphInfo {
    private:
        int v1, v2; // Edge of the graph
        int be;     // Edge's benefit
        int ce;     // Edge's cost
    public:
        GraphInfo(int, int, int, int);

        // Benefit of crossing an edge once
        int crossEdgeOnce()  { return be - ce; }

        // Benefit of crossing an edge twice
        int crossEdgeTwice() { return be - 2 * ce; }
};

// Constructor
GraphInfo::GraphInfo (int v1, int v2, int be, int ce) {
  this->v1 = v1;
  this->v2 = v2;
  this->be = be;
  this->ce = ce;
}

/**************************************************************************//**
 *  Graph. List of the edges and it's benefits and costs
 *****************************************************************************/
class Graph {
    private:
        std::list<GraphInfo> edges;
    public:
        Graph(std::list<GraphInfo> & edges);
        //FUNCIONES QUE PODRIA TENER, AUN NO ESTOY SEGURA
        void MST();
        void isEulerian();
        void isConnected();
        void connectedComponents();
};

// Constructor
Graph::Graph (std::list<GraphInfo> & edges) {
    this->edges = edges;
}

#endif // _GRAPH_HPP
