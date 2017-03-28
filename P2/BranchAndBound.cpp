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
using namespace std;

std::vector< vector<DEdge> > solParcial;
std::vector< vector<DEdge> > mejorSol;
int beneficioDisponible; //obtener_max_beneficio(); // benefit of the greedy algorithm
std::unordered_set<int> vertexInSol = {0};
time_t timeStart;
time_t timeEnd;
double tDiff;
ofstream statsFile; //File to be read

//calculamos el beneficio del grafo que se esta construyendo
int beneficio(vector<vector<DEdge>> solucion){

    int  be = 0;
    int  ce = 0;
    int  vactual = 0;
    int  beneficio = 0;
    bool fincamino = false;

    //calculamos el beneficio hasta retornar al nodo origen
    while (!fincamino){
        be = solucion[vactual][0].get_benefit();
        ce = solucion[vactual][0].get_cost();
        beneficio += be - ce;
        vactual = solucion[vactual][0].get_vIn();
        if(vactual == 0) {fincamino = true;};

    };

    return beneficio;

};

bool cicloNegativo(int v, DEdge e, vector<vector<DEdge>> solucion){

    int vactual = e.get_vIn();
    int be = 0;
    int ce = 0;
    int beneficio = 0;

    //recorremos el camino justo antes encontrarnos con el arco a agregar
    while(vactual != v){
        be = solucion[vactual][0].get_benefit();
        ce = solucion[vactual][0].get_cost();
        beneficio += be - ce;
        vactual = solucion[vactual][0].get_vIn();
    };

    //agregamos el beneficio de recorrer el nuevo arco a agregar
    beneficio += e.get_benefit() - e.get_cost();

    return (beneficio < 0);


};

bool estaLadoEnSolParcial(int v, DEdge e, vector<vector<DEdge>> solucion){

    for(vector<DEdge>::iterator it = solucion[v].begin(); it != solucion[v].end(); ++it){

        if (e == *it) {return true;}
    };

    return false;
};

bool cumpleAcotamiento(int v, DEdge e, vector<vector<DEdge>> & solucion){

    int beneficioE = e.get_benefit() - e.get_cost();
    int beneficioparcial = beneficio(solucion) + beneficioE;
    int beneficiomaximo = beneficioDisponible + beneficioparcial - max(0,beneficioE);
    if (beneficiomaximo <= beneficio(mejorSol)) {

        return false;
    }

    else{

        return true;
    }
};

void agregarLado(int v, DEdge e, vector<vector<DEdge>> solucion){

    //procedemos a revisar si el arco en direccion opuesta ya fue insertado
    int v1 = e.get_vIn();
    int v2 = v;
    int be = e.get_benefit();
    int ce = e.get_cost();

    //en caso de encontrar el arco inverso en la solucion, agregamos el nuevo arco con beneficio 0;
    for(vector<DEdge>::iterator it = solucion[v1].begin(); it != solucion[v1].end(); ++it){

        if(it -> get_vIn() == v2){
            be = 0;
        }
    }

    DEdge nuevo(v1,ce,be);
    solucion[v].push_back(nuevo);

};


void DFS(int v, DGraph & grafo) {
    
    if (v == 0){
        if (beneficio(solParcial) > beneficio(mejorSol)){
            std::copy(solParcial.begin(),solParcial.end(),mejorSol.begin());
        }
    }

    vector<DEdge> sucesores = grafo.get_successor_list(v);

    for (vector<DEdge>::iterator it = sucesores.begin(); it != sucesores.end(); ++it){

        int v2 = it -> get_vIn();
        int be = it -> get_benefit();
        int ce = it -> get_cost();
        
        if (!cicloNegativo(v,*it,solParcial) && !estaLadoEnSolParcial(v,*it,solParcial) &&
            //!repiteCiclo(v,*it,solParcial) && 
            cumpleAcotamiento(v,*it,solParcial)){

            agregarLado(v,*it,solParcial);
            beneficioDisponible -= max(0,be-ce);
            DFS(v2,grafo);

        };
    };

    //DEge e = eliminarUltimoLado(solParcial);
    //beneficioDisponible += max(0,e.get_benefit() - e.get_cost());
    
};

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
    //holas
}
