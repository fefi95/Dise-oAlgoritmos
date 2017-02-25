/**
 *  Universidad Simon Bolivar
 *  CI-5651 - Diseño de Algoritmos I
 *  @author : Salvador Di Renzo 10-10296
 *  @author : Stefani Castellanos 11-11394
 *
 *
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include "Reader.hpp"
#include "Writer.hpp"

using namespace std;

// % Standard deviation
float pStd(int vo, int vh) {
    // return 100*((vo - vh)/vo);
    return 0.0;
}

int main(int argc, char **argv) {

    int vo;
    int vhp;
    time_t timeStart;
    time_t timeEnd;
    double tHeur;

    ofstream aFile;
    aFile.open("ALBAIDA.csv");
    aFile << "Instancia, Vo, \%dHeurPlanos, \%dHeur, tHeur (seg) " << std::endl;
    float dHeur;
    float dvhp;

    //ALBAIDAA
    Graph graphAA = readFile("instanciasPRPP/ALBAIDA/ALBAIDAANoRPP");
    vo = 6266;
    vhp = 6247;
    timeStart = time(NULL);
    std::pair < int,std::vector<int> > solA  = graphAA.solvePRPP();
    timeEnd = time(NULL);
    tHeur = difftime(timeEnd, timeStart);
    // get standard deviations
    dvhp = pStd(vo, vhp);
    dHeur = pStd(vo, solA.first);
    writeFile("instanciasPRPP/ALBAIDA/ALBAIDAANoRPP-salida.txt", solA);
    aFile << "ALBAIDAA, " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;

    //ALBAIDAB
    Graph graphAB = readFile("instanciasPRPP/ALBAIDA/ALBAIDABNoRPP");
    timeStart = time(NULL);
    vo = 4372;
    vhp = 4372;
    std::pair < int,std::vector<int> > solB  = graphAB.solvePRPP();
    timeEnd = time(NULL);
    tHeur = difftime(timeEnd, timeStart);
    // get standard deviations
    dvhp = pStd(vo, vhp);
    dHeur = pStd(vo, solB.first);
    writeFile("instanciasPRPP/ALBAIDA/ALBAIDABNoRPP-salida.txt", solB);
    aFile << "ALBAIDAB, " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
    aFile.close();

    // CHRISTOFIDES
    ofstream chFile;
    chFile.open("christofides.csv");
    chFile << "Instancia, Vo, \%dHeurPlanos, \%dHeur, tHeur (seg) " << std::endl;
    int chVo[24] = {3,66,56,45,35,60,89,90,46,41,9,10,5,128,43,113,42,21,90,246,258,474,360,237};
    int chVhp[24] = {3,66,56,45,35,60,89,90,45,41,9,10,5,128,39,106,39,17,90,246,252,474,360,230};
    char file[1024];
    for (int i = 1; i < 25; i++) {
        if (i < 10){
            sprintf(file, "instanciasPRPP/CHRISTOFIDES/P0%dNoRPP", i);
        }
        else {
            sprintf(file, "instanciasPRPP/CHRISTOFIDES/P%dNoRPP", i);
        }
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::pair < int,std::vector<int> > sol  = graph.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(chVo[i-1], chVhp[i-1]);
        dHeur = pStd(chVo[i-1], sol.first);
        writeFile(strcat(file,"-salida.txt"), sol);
        chFile << "P" << i << ", " << chVo[i-1] << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
        memset(file, '\0', 1024);
    }
    chFile.close();

    // DEGREE
    ofstream dFile;
    dFile.open("degree.csv");
    dFile << "Instancia, Vo, \%dHeurPlanos, \%dHeur, tHeur (seg) " << std::endl;
    int dVo[36] = {109,115,274,172,210,313,166,260,457,160,0,398,280,717,810,702,980,1115,515,509,457,1000,989,968,1463,1317,1625,549,815,55,1378,1503,1066,2074,1806,1901};
    int dVhp[36] = {109,115,274,172,210,313,166,260,457,160,0,398,280,662,810,702,965,1070,515,509,457,976,989,968,1463,1317,1610,501,786,517,1378,1503,1028,2074,1806,1820};
    for (int i = 0; i < 36; i++) {
        sprintf(file, "instanciasPRPP/DEGREE/D%dNoRPP", i);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::pair < int,std::vector<int> > sol  = graph.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(dVo[i], dVhp[i]);
        dHeur = pStd(dVo[i], sol.first);
        writeFile(strcat(file,"-salida.txt"), sol);
        dFile << "D" << i << ", " << dVo[i] << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
        memset(file, '\0', 1024);
    }
    dFile.close();

    // GRID
    ofstream grFile;
    grFile.open("grid.csv");
    grFile << "Instancia, Vo, \%dHeurPlanos, \%dHeur, tHeur (seg) " << std::endl;
    int grVo[36] = {0,0,0,2,0,4,9,1,4,2,0,4,15,11,14,26,20,24,8,6,9,32,32,33,57,46,57,14,23,14,50,54,57,92,86,88};
    int grVhp[36] = {0,0,0,2,0,4,9,1,4,2,0,4,15,11,14,26,20,24,8,6,9,32,31,33,57,46,57,14,22,13,50,54,55,92,86,87};
    for (int i = 0; i < 36; i++) {
        sprintf(file, "instanciasPRPP/GRID/G%dNoRPP", i);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::pair < int,std::vector<int> > sol  = graph.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(grVo[i], grVhp[i]);
        dHeur = pStd(grVo[i], sol.first);
        writeFile(strcat(file,"-salida.txt"), sol);
        grFile << "G" << i << ", " << grVo[i] << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
        memset(file, '\0', 1024);
    }
    grFile.close();

    // RANDOM
    ofstream rFile;
    rFile.open("random.csv");
    rFile << "Instancia, Vo, \%dHeurPlanos, \%dHeur, tHeur (seg) " << std::endl;
    int rVo[20] = {1742,4253,5638,18453,17316,398,12478,9405,14847,17405,7125,1493,32453,30732,27791,10533,4276,28462,26873};
    int rVhp[20] = {1742,4253,5638,18453,17316,398,12478,9405,14847,17405,7125,1493,30464,30732,27791,10533,4001,28462,26873};
    for (int i = 0; i < 20; i++) {
        sprintf(file, "instanciasPRPP/RANDOM/R%dNoRPP", i);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::pair < int,std::vector<int> > sol  = graph.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(rVo[i], rVhp[i]);
        dHeur = pStd(rVo[i], sol.first);
        writeFile(strcat(file,"-salida.txt"), sol);
        rFile << "R" << i << ", " << rVo[i] << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
        memset(file, '\0', 1024);
    }
    rFile.close();

}
