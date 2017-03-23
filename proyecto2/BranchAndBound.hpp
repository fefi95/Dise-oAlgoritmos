/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *  Information of the graph
 */

DGraph grafo = readFile2(argv[1]);
std::vector< vector< DEdge > sol;
std::vector<DEdge> sucesores_d;
sol.push_back(sucesores_d);
DGraph solParcial(1, sol);
Dgraph mejorSol(1, sol);
int beneficioDisponible = obtener_max_beneficio(); // benefit of the greedy algorithm

void DFS(int v) {
    if (v == 0 && (solParcial.beneficio()) > mejorSol.beneficio())) {
        mejorSol = solParcial; //clone
    }
    L = grafo.get_successor_list(v);
    for (int i = 0; i < L.size(); i++) {
        DEdge e = L[i];
        int vj = e.get_vIn();
        int be = e.get_benefit();
        int ce = e.get_cost();
        if (!ciclo_negativo(v, e, solParcial) &&
            !esta_lado_en_sol_parcial(v, e, solParcial) &&
            !repite_ciclo(v, e, solParcial) &&
            !cumple_acotamiento(v, e, solParcial)
            ) {
                agragar_lado(v, e, solParcial);
                beneficioDisponible = beneficioDisponible − max(0, be − ce);
                DFS(vj);
            }
    }

    DEdge e = eliminar_ultimo_lado(solParcial);
    int be = e.get_benefit();
    int ce = e.get_cost();
    beneficioDisponible = beneficioDisponible + max(0, be − ce);
}

DEdge eliminar_ultimo_lado(solParcial){
    // inserte su codigo aqui
}

bool ciclo_negativo(v, e, solParcial) {
    // inserte su codigo aqui
    return false;
}

bool esta_lado_en_sol_parcial(v, e, solParcial) {
    // insert su codigo aqui
    return false;
}

bool repite_ciclo(v, e, solParcial) {
    // inserte su codigo aqui
    return false;
}

bool cumple_acotamiento(v, e, solParcial) {
    // inserte su codigo aqui
    return true;
}
// Input: Un grafo G = (V, E) y un ciclo solInicial soluci´on de PRPP
// Output: Un ciclo C , soluci´on ´optima de PRPP
// begin
//      solParcial ←< d > // Variable Global
//      mejorSol ←solInicial // Variable Global
//      beneficioDisponible ← obtener-max-beneficio(G) // Variable Global
//      busqueda-en-Profundidad()

// busqueda-en-Profundidad()
// begin
//      v ← vertice-mas-externo(solParcial)
//      // Vemos si se encuentra una mejor soluci´on factible
//       if (v = d) then
//          if (beneficio(solParcial) > beneficio(mejorSol)) then
//          mejorSol ← solParcial
//       L(v) ← obtener-lista-de-sucesores(v) // Lista de aristas
//       foreach e ∈ L(v) do
//           if (¬ciclo-negativo(e, solParcial) ∧
//          ¬esta-lado-en-sol-parcial(e, solParcial) ∧
//          ¬repite-ciclo(L(v), e, solParcial) ∧
//          cumple-acotamiento(e, solParcial)) then
//           agregar-lado(e, solParcial)
//           beneficioDisponible = beneficioDisponible − max(0, be − ce)
//           busqueda-en-Profundidad()
//       e = eliminar-ultimo-lado(solParcial)
//       beneficioDisponible = beneficioDisponible + max(0, be − ce)

// func obtener-lista-de-sucesores(v: v´ertice)
// begin
//     L(v) ← ∅
//     foreach arista e incidente a v do
//     L(v) ← agregar una arista e1 con beneficio be y costo ce
//     L(v) ← agregar una arista e2 con beneficio 0 y costo ce
//     Ordenar de manera descendente a L(v) seg´un su beneficio
//     return L(v)
// func ciclo-negativo(e: arista, solParcial: Secuencia de aristas)
//      begin
//      if al agregar la arista e a la soluci´on parcial solParcial se forma un ciclo con beneficio negativo then
//         return Verdadero
//      return Falso
//
// func esta-lado-en-sol-parcial(e: arista, solParcial: Secuencia de aristas)
//     begin
//     if la arista e no se encuentra en solParcial then
//         return Falso
//     else if la arista e se encuentra una vez en solParcial then
//         if be = 0 then // La arista se recorre por segunda vez
//             return Falso
//         else
//             return Verdadero
//     else
//         return Verdadero

// func repite-ciclo(L(v): Lista de Aristas, e: arista, solParcial: Secuencia de aristas)
//     begin
//     if al agregar e en solParcial se forma un ciclo con una arista e' then
//     if (e' ∈ solParcial ∧ ((be − ce) < (be' − ce'))) then
//         return Falso
//     else
//         return Verdadero
//     return Falso

// func cumple-acotamiento(e: arista, solParcial: Secuencia de aristas)
//     begin
//     beneficioE ← be − ce
//     beneficioSolParcial ← beneficio(solParcial) + beneficioE
//     maxBeneficio ← beneficioDisponible − max(0, beneficioE) + beneficioSolParcial
//     if (maxBeneficio ≤ beneficio(mejorSol)) then return Falso
//     return Verdadero
