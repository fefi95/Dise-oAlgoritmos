/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo
 *  @author : Stefani Castellanos 11-11394
 *
 *  Implementation for a graphs respresenteed as a list of edges
 */

#ifndef _GRAPHINFO_HPP
#define _GRAPHINFO_HPP

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
  v1 = v1;
  v2 = v2;
  be = be;
  ce = ce;
}

#endif // _GRAPHINFO_HPP
