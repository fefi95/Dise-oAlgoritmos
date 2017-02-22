/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Information of the graph
 */

#ifndef _UNION_FIND_HPP
#define _UNION_FIND_HPP

#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <vector>

using namespace std;

/**************************************************************************//**
 *  Edge. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
 class Union_find {
   int *parent; // Array of parents
   int cont;    // Number of disjoint sets
   int *sz;     // Size of disjoint set
   public:
        // Create an empty union find data structure with N isolated sets.
        Union_find (int);
        int find(int p);
        void set_union(int x, int y);
        bool connected(int x, int y);

        // Return the number of disjoint sets.
        int count() { return cont; }
};

// Constructor
Union_find::Union_find(int N) {
    cont = N; parent = new int[N]; sz = new int[N];
    for (int i = 0; i<N; i++)  parent[i] = i, sz[i] = 1;
}

// Return the parent of component corresponding to object p.
int Union_find::find(int p) {
    int root = p;
    while (root != parent[root])    root = parent[root];
    while (p != root) { int newp = parent[p]; parent[p] = root; p = newp; }
    return root;
}

// Replace sets containing x and y with their union.
void Union_find::set_union(int x, int y) {
    int i = find(x); int j = find(y); if (i == j) return;
    // make smaller root point to larger one
    if (sz[i] < sz[j]) {
        parent[i] = j;
        sz[j] += sz[i];
    }
    else {
        parent[j] = i;
        sz[i] += sz[j];
    }
    --cont;
}

// Are objects x and y in the same set?
bool Union_find::connected(int x, int y) { return find(x) == find(y); }

#endif // _UNION_FIND_HPP
