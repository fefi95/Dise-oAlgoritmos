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
