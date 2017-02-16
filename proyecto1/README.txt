-------------------------------------------------------------------------------
IDEA 1 - Dijkstra
-------------------------------------------------------------------------------
Dijkstra order by (be - 2ce)

-------------------------------------------------------------------------------
IDEA 2 - A Eulerian cycle is a feasible solution (simplified)
-------------------------------------------------------------------------------
G' <- disconnect vertex d from G(V,R) (original graph)
G'.MST
add minimum cost edges for those vertex of odd degree.
add minimum cost edges that connect the MST with D.

-------------------------------------------------------------------------------
IDEA 3 - Eulerian Graph is a feasible solution
-------------------------------------------------------------------------------
Gr <- Edges of the original graph (G(Vr, Er)) such that be - 2ce >= 0
if Gr.eulerianGraph then
    return solution
else if Gr.connectedGraph then
    addEdges
    return solution

else
    Gt <- Graph Gt(Vc, Ec) where Vc are the connected components of G and Ec
          the edge of minimum cost that two connected components.
    G' <- Graph G'(Vr, Ec U Er)
    G'.MST (Kruskall or Prim)
    add minimum cost edges for those vertex of odd degree.
    return solution

-------------------------------------------------------------------------------
Note: none of this approaches finds the actual solution for the PRPP but
provides a feasible solution.
-------------------------------------------------------------------------------
