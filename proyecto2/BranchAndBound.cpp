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
#include <ctime>
#include <iostream>
#include <fstream>
#include "Reader.hpp"
#include "DGraph.hpp"

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
    std::cout << "" << std::endl;
    std::cout << "BENEFICIOOOOOO    " << std::endl;
    while (!graph[vOut].empty() && vOut < graph.size()) {
        DEdge edge = graph[vOut][0]; // First element
        std::cout <<  edge << std::endl;
        (graph[vOut]).erase((graph[vOut]).begin());
        benefit += edge.get_benefit() - edge.get_cost();
        vOut = edge.get_vIn();
    }
    std::cout << "" << std::endl;
    return benefit;
}

void printSol(std::vector< vector<DEdge> > sol) {
    int vOut = 0; // source
    while (!sol[vOut].empty() && vOut < sol.size()) {
        DEdge edge = sol[vOut][0]; // First element
        std::cout << vOut + 1 << " - ";
        // std::cout << edge << std::endl;
        sol[vOut].erase(sol[vOut].begin());
        vOut = edge.get_vIn();
    }
    std::cout << vOut + 1 << std::endl;
    // std::cout << std::endl;
}
void agregar_lado(int v, DEdge e, std::vector< vector<DEdge> >& solParcial){
    vertexInSol.insert(e.get_vIn());
    std::cout << "myset contains:";
    for ( int x: vertexInSol ) std::cout << " " << x+1;
    std::cout << std::endl;
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
    // std::cout << "edge to delete "<< vToDelete+1 << e << std::endl;
    if (!solParcial[vToDelete].empty()){
        printEdges(cout, solParcial[vToDelete]);
        // std::cout << *(solParcial[vToDelete].begin() + vOut) << std::endl;
        // std::vector< vector<DEdge> >::iterator it = solParcial[vToDelete].begin();
        // it += vOut;
        solParcial[vToDelete].erase(solParcial[vToDelete].end());
        vertexInSol.erase(vOut);
    }
    return e;
}

bool esta_lado_en_sol_parcial(int v, DEdge e, std::vector< vector<DEdge> > solParcial) {

    for(std::vector<DEdge>::iterator edge = solParcial[v].begin(); edge != solParcial[v].end(); ++edge) {
        // Edge was found
        if (e == *edge) {
            // std::cout << "esta lado " << v+1 << " - " << e << std::endl;
            return true;
        }
    }

    for(std::vector<DEdge>::iterator edge = solParcial[e.get_vIn()].begin(); edge != solParcial[e.get_vIn()].end(); ++edge) {
        // Edge was found
        if (edge -> get_vIn() == v && edge -> get_benefit() == e.get_benefit()) {
            // if (e.get_benefit() == 0) {
            //     std::cout << "beneficio 0" << std::endl;
            //     return false;
            // }
            // else {
                // std::cout << "esta lado " << v+1 << " - " << e << std::endl;
                return true;
            // }
        }
    }
    std::cout << "noooooooooo" <<  v+1 << " - " << e << std::endl;
    return false;
}

// func ciclo-negativo(e: arista, solParcial: Secuencia de aristas)
//      begin
//      if al agregar la arista e a la soluci´on parcial solParcial se forma un ciclo con beneficio negativo then
//         return Verdadero
//      return Falso
//

bool ciclo_negativo(int v, DEdge e, std::vector< vector<DEdge> > solParcial) {
    std::unordered_set<int>::iterator find = vertexInSol.find(v);

    if ( find != vertexInSol.end() ) { // is not a cycle
        return false;
    }
    else {
        int benefit = 0;
        int vOut = v; // source
        // std::cout << "" << std::endl;
        while (!solParcial[vOut].empty() && vOut < solParcial.size()) {
            DEdge edge = solParcial[vOut][0]; // First element
            // std::cout <<  edge << std::endl;
            (solParcial[vOut]).erase((solParcial[vOut]).begin());
            benefit += edge.get_benefit() - edge.get_cost();
            vOut = edge.get_vIn();
        }
        // std::cout << "" << std::endl;
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
    std::cout << "benefit parcial" << beneficioSolParcial << std::endl;
    int maxBeneficio = beneficioDisponible - max(0, beneficioE) + beneficioSolParcial;
    // int maxBeneficio = beneficioSolParcial;
    std::cout << "compara beneficio " << maxBeneficio << " " << benefit(mejorSol)  << std::endl;
    if (maxBeneficio <= benefit(mejorSol)){
        // std::cout << " no cumple_acotamiento" << std::endl;
        return false;
    }
    // std::cout << "cumple_acotamiento" << std::endl;
    return true;
}

void DFS(int v, DGraph& grafo) {
    // std::cout << "benefit " << benefit(solParcial) << " " << benefit(mejorSol) << std::endl;
    std::cout << "v " << v+1 << std::endl;
    if (v == 0 && (benefit(solParcial) > benefit(mejorSol))) {
        std::cout << "COPY" << std::endl;
        std::copy(solParcial.begin(), solParcial.end(), mejorSol.begin());
    }
    std::vector<DEdge> L = grafo.get_successor_list(v);
    printEdges(cout, L);
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
                std::cout << "agregando lado.." << v+1 << e << std::endl;
                agregar_lado(v, e, solParcial);
                printSol(solParcial);
                // int nrows;
                // cin >> nrows;
                beneficioDisponible = beneficioDisponible - max(0, be - ce);
                std::cout << "Beneficio dispon" << beneficioDisponible << std::endl;
                timeEnd = time(NULL);
                tDiff = difftime(timeEnd, timeStart);
                if (tDiff > 600) { // 10 min
                    std::cout << "TIME OUT" << std::endl;
                    statsFile << "-T-" << std::endl;
                    exit(0);
                }
                DFS(vj, grafo);
            }
    }

    std::cout << "ANTES DE ELIMINAR" << std::endl;
    printSol(solParcial);
    DEdge e = eliminar_ultimo_lado(solParcial, solParcial);
    printSol(solParcial);
    int be = e.get_benefit();
    int ce = e.get_cost();
    beneficioDisponible = beneficioDisponible + max(0, be - ce);
    std::cout << "Beneficio dispon" << beneficioDisponible << std::endl;
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
    DGraph grafo = readFile2(argv[1]);
    statsFile.open(argv[2], std::ios::out | std::ios::app);
    for (int i = 0; i < grafo.get_n_vertex(); i++) {
        std::vector<DEdge> adjacent;
        solParcial.push_back(adjacent);
        mejorSol.push_back(adjacent);
    }
    beneficioDisponible = get_max_benefit(strcat(argv[1],"-salida.txt"));
    if (beneficioDisponible < 0) {
        beneficioDisponible = 0;
    }
    std::cout << "Beneficio dispon" << beneficioDisponible << std::endl;
    // name, optimum, heuristic value, heuristic deviation,
    float optimum = stof(argv[4]);
    statsFile << argv[3] << "," << optimum << "," << beneficioDisponible << "," << pStd(optimum, beneficioDisponible) << "," << std::endl;
    timeStart = time(NULL);
    DFS(0, grafo);
    printSol(mejorSol);
    std::cout << benefit(mejorSol) << std::endl;
    // time bnb
    statsFile << tDiff << std::endl;
}
