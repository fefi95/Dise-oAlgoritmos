/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Information of the graph
 */

#include <algorithm>
#include <unordered_set>
#include <set>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Reader.hpp"
#include "DGraph.hpp"
#include "Graph.hpp"

std::vector< vector<DEdge> > solParcial;
std::vector< vector<DEdge> > mejorSol;
int beneficioDisponible; //obtener_max_beneficio(); // benefit of the greedy algorithm
std::unordered_set<int> vertexInSol = {0};
time_t timeStart;
time_t timeEnd;
double tDiff;
ofstream statsFile; //File to be read

int benefit(std::vector< vector<DEdge> > graph) {
    int benefit = 0;
    int vOut = 0; // source
    while (!graph[vOut].empty() && vOut < graph.size()) {
        DEdge edge = graph[vOut][0]; // First element
        (graph[vOut]).erase((graph[vOut]).begin());
        benefit += edge.get_benefit() - edge.get_cost();
        vOut = edge.get_vIn();
    }
    return benefit;
}

void printSol(std::vector< vector<DEdge> > sol) {
    int vOut = 0; // source
    while (!sol[vOut].empty() && vOut < sol.size()) {
        DEdge edge = sol[vOut][0]; // First element
        sol[vOut].erase(sol[vOut].begin());
        vOut = edge.get_vIn();
    }
}

void agregar_lado(int v, DEdge e, std::vector< vector<DEdge> >& solParcial){
    vertexInSol.insert(e.get_vIn());
    solParcial[v].push_back(e);
}

DEdge eliminar_ultimo_lado(std::vector< vector<DEdge> > sol, std::vector< vector<DEdge> >& solParcial) {
    int vOut = 0; // source
    int vToDelete = 0;
    int be = 0;
    int ce = 0;
    while (!sol[vOut].empty() && vOut < sol.size()) {
        DEdge edge = sol[vOut][0]; // First element
        sol[vOut].erase(sol[vOut].begin());
        be = edge.get_benefit();
        ce = edge.get_cost();
        vToDelete = vOut;
        vOut = edge.get_vIn();
    }
    DEdge e(vOut, ce, be);
    if (!solParcial[vToDelete].empty()){
        solParcial[vToDelete].erase(solParcial[vToDelete].end());
        vertexInSol.erase(vOut);
    }
    return e;
}

bool esta_lado_en_sol_parcial(int v, DEdge e, std::vector< vector<DEdge> > solParcial) {

    int cont = 0;
    for(std::vector<DEdge>::iterator edge = solParcial[v].begin(); edge != solParcial[v].end(); ++edge) {
        if (e.get_vIn() == edge -> get_vIn()){
            cont += 1;
        }
    }
    for(std::vector<DEdge>::iterator edge = solParcial[e.get_vIn()].begin(); edge != solParcial[e.get_vIn()].end(); ++edge) {
        if (v == edge -> get_vIn()) {
            cont += 1;
        }
    }
    if (cont == 1) {
        if (e.get_benefit() == 0){
            return false;
        }
        else {
            return true;
        }
    }
    else if (cont < 1) {
        return false;
    }
    return true;
}

// func ciclo-negativo(e: arista, solParcial: Secuencia de aristas)
//      begin
//      if al agregar la arista e a la soluci´on parcial solParcial se forma un ciclo con beneficio negativo then
//         return Verdadero
//      return Falso
//

bool ciclo_negativo(int v, DEdge e, std::vector< vector<DEdge> > solParcial) {
    std::unordered_set<int>::iterator find = vertexInSol.find(v);

    if ( find == vertexInSol.end() ) { // is not a cycle
        return false;
    }
    else {
        int benefit = 0;
        int vOut = e.get_vIn(); // source
        while (!solParcial[vOut].empty() && vOut < solParcial.size()) {
            DEdge edge = solParcial[vOut][0]; // First element
            (solParcial[vOut]).erase((solParcial[vOut]).begin());
            benefit += edge.get_benefit() - edge.get_cost();
            vOut = edge.get_vIn();
        }
        benefit += e.get_benefit() - e.get_cost();
    }
    return (benefit < 0);
}

// func repite-ciclo(L(v): Lista de Aristas, e: arista, solParcial: Secuencia de aristas)
//     begin
//     if al agregar e en solParcial se forma un ciclo con una arista e' then
//     if (e' ∈ solParcial ∧ ((be − ce) < (be' − ce'))) then
//         return Falso
//     else
//         return Verdadero
//     return Falso

bool repite_ciclo(int v, DEdge e, std::vector< vector<DEdge> > solParcial) {
    // inserte su codigo aqui
    return false;
}

// func cumple-acotamiento(e: arista, solParcial: Secuencia de aristas)
//     begin
//     beneficioE ← be − ce
//     beneficioSolParcial ← beneficio(solParcial) + beneficioE
//     maxBeneficio ← beneficioDisponible − max(0, beneficioE) + beneficioSolParcial
//     if (maxBeneficio ≤ beneficio(mejorSol)) then return Falso
//     return Verdadero
bool cumple_acotamiento(int v, DEdge e, std::vector< vector<DEdge> > solParcial) {
    int beneficioE = e.get_benefit() - e.get_cost();
    int beneficioSolParcial = benefit(solParcial) + beneficioE;
    int maxBeneficio = beneficioDisponible - max(0, beneficioE) + beneficioSolParcial;
    if (maxBeneficio < benefit(mejorSol)){
        return false;
    }
    return true;
}

void DFS(int v, DGraph& grafo) {
    if (v == 0 && (benefit(solParcial) > benefit(mejorSol))) {
        std::copy(solParcial.begin(), solParcial.end(), mejorSol.begin());
    }
    std::vector<DEdge> L = grafo.get_successor_list(v);
    for (int i = 0; i < L.size(); i++) {
        DEdge e = L[i];
        int vj = e.get_vIn();
        int be = e.get_benefit();
        int ce = e.get_cost();
        if (!ciclo_negativo(v, e, solParcial) &&
            !esta_lado_en_sol_parcial(v, e, solParcial) &&
            !repite_ciclo(v, e, solParcial) &&
            cumple_acotamiento(v, e, solParcial)
            ) {
                agregar_lado(v, e, solParcial);
                beneficioDisponible = beneficioDisponible - max(0, be - ce);
                timeEnd = time(NULL);
                tDiff = difftime(timeEnd, timeStart);
                if (tDiff > 1800) { // 10 min
                    std::cout << "TIME OUT" << std::endl;
                    statsFile << "-T-" << std::endl;
                    exit(0);
                }
                DFS(vj, grafo);
            }
    }

    DEdge e = eliminar_ultimo_lado(solParcial, solParcial);
    int be = e.get_benefit();
    int ce = e.get_cost();
    beneficioDisponible = beneficioDisponible + max(0, be - ce);
}

// Input: Un grafo G = (V, E) y un ciclo solInicial soluci´on de PRPP
// Output: Un ciclo C , soluci´on ´optima de PRPP
// begin
//      solParcial ←< d > // Variable Global
//      mejorSol ←solInicial // Variable Global
//      beneficioDisponible ← obtener-max-beneficio(G) // Variable Global
//      busqueda-en-Profundidad()

// % Standard deviation
float pStd(float vo, float vh) {
    if (vo == 0){
        return 0;
    }
    return 100*((vo - vh)/vo);
}

int main(int argc, char **argv) {

    // Greedy solution
    Graph graph = readFile(argv[1]);
    std::pair < int,std::vector<int> > sol  = graph.solvePRPP();

    DGraph grafo = readFile2(argv[1]);

    for (int i = 0; i < grafo.get_n_vertex(); i++) {
        std::vector<DEdge> adjacent;
        solParcial.push_back(adjacent);
        mejorSol.push_back(adjacent);
    }

    std::set< pair <int, int> > isInSol;
    std::pair<int, int> edgeInSol;
    int be = 0;
    int ce = 0;
    int v1, v2;

    for (int i = 0; i < sol.second.size()-1; i++) {
        v1 = sol.second[i]-1;
        v2 = sol.second[i+1]-1;

        edgeInSol.first = v2;
        edgeInSol.second = v1;
        std::set<pair<int, int>>::iterator find = isInSol.find(edgeInSol);
        std::vector<DEdge> adjacent = grafo.get_graph()[v1];
        for(std::vector<DEdge>::iterator it =  adjacent.begin(); it != adjacent.end(); ++it) {
            if (it -> get_vIn() == v2) {
                be = it -> get_benefit();
                ce = it -> get_cost();
                break;
            }
        }
        if (find != isInSol.end()) { // not found
            be = 0;
        }
        DEdge e(v2, ce, be);
        mejorSol[v1].push_back(e);
        std::pair<int,int> e2(v1,v2);
        isInSol.insert(e2);
    }
    statsFile.open(argv[2], std::ios::out | std::ios::app);


    beneficioDisponible = atoi(argv[4]);
    // name, optimum, heuristic value, heuristic deviation,
    float optimum = stof(argv[4]);
    statsFile << argv[3] << "," << optimum << "," << sol.first << "," << pStd(optimum, sol.first) << "," << std::endl;
    timeStart = time(NULL);
    DFS(0, grafo);
    printSol(mejorSol);
    std::cout << benefit(mejorSol) << std::endl;
    // time bnb
    statsFile << tDiff << std::endl;
}
