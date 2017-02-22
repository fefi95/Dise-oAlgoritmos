/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Information of the graph
 */

#ifndef _UNION-FIND_HPP
#define _UNION-FIND_HPP

#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <vector>

using namespace std;

/**************************************************************************//**
 *  Edge. Information of an edge of the graph, it's benefit and cost.
 *****************************************************************************/
class Union_Find {
    private:
        int parent;
        int rank;
    public:
        Union_Find(int);
};

// Constructor
Union_Find::Union_Find (int value) {
  // this -> value = value;
  this -> parent = value;
  this -> rank = 0;
}

Union_Find union (Union_Find x, Union_Find y) {
    return link(find_set(x), find_set(y));
}

Union_Find find (Union_Find x) {
    if (x != x.parent) {
        x.parent = find(x.parent);
    }
}
Union_Find link(Union_Find x, Union_Find y) {
    if (x.rank > y.rank){
        y.parent = x;
    }
    else {
        x.parent = y
        if (x.rank == y.rank) {
            ++y.rank;
        }
    }
}

#endif // _UNION-FIND_HPP
