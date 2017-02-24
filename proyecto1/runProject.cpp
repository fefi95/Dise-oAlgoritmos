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
#include <string>
#include <ctime>
#include "Reader.hpp"
#include "Writer.hpp"

using namespace std;

int main(int argc, char **argv) {

    char* noRPP = "noRPP";
    ofstream sourcefile; //File to be written
    sourcefile.open(file);
    if(sourcefile.is_open()){ return 0 };
    int vo;
    int vhp;
    time_t timeStart;
    time_t timeEnd;
    double tHeur;

    ofstream aFile;
    aFile.open("ALBAIDA.csv");
    aFile << "Instancia, Vo, \%dHeurPlanos, \%dHeur, tHeur (seg) ";
    float dHeur;
    float dvhp;
    int vHeur;

    //ALBAIDAA
    Graph graphAA = readFile("instanciasPRPP/ALBAIDAA/ALBAIDAANoRPP");
    vo = 6266;
    vhp = 6247;
    timeStart = time(NULL);
    std::vector< vector<int> > sol  = graphAA.solvePRPP();
    timeEnd = time(NULL);
    tHeur = difftime(timeEnd, timeStart);
    writeFile("ALBAIDAANoRPP-salida.txt", sol, vHeur);
    aFile << "ALBAIDAA, " << vo << ", " << vhp << ", " << dHeur << ", " << tHeur << std::endl;

    //ALBAIDAB
    Graph graphAB = readFile("instanciasPRPP/ALBAIDAA/ALBAIDABNoRPP");
    timeStart = time(NULL);
    vo = 4372;
    vhp = 4372;
    std::vector< vector<int> > sol  = graphAB.solvePRPP();
    timeEnd = time(NULL);
    tHeur = difftime(timeEnd, timeStart);
    // get standard deviations
    dvhp = pStd(vo, vhp);
    dHeur = pStd(vo, vHeur);
    writeFile("ALBAIDABNoRPP-salida.txt", sol, vHeur);
    aFile << "ALBAIDAB, " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
    aFile.close();

    // CHRISTOFIDES
    ofstream chFile;
    chFile.open("christofides.csv");
    int chVo[24] = {3,66,56,45,35,60,89,90,46,41,9,10,5,128,43,113,42,21,90,246,258,474,360,237};
    int chVhp[24] = {3,66,56,45,35,60,89,90,45,41,9,10,5,128,39,106,39,17,90,246,252,474,360,230};
    for (int i = 1; i < 25; i++) {
        char* name;
        if (i < 10){
            name = strcat("instanciasPRPP/CHRISTOFIDES/P0", i);
        }
        else {
            name = strcat("instanciasPRPP/CHRISTOFIDES/P", i);
        }
        char* file = strcat(name, noRPP);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::vector< vector<int> > sol  = graphAB.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(chvo[i-1], chVhp[i-1]);
        dHeur = pStd(chvo[i-1], vHeur);
        writeFile(strcat(file,"-salida.txt"), sol, vHeur);
        chFile << "P" << i << ", " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
    }
    chFile.close();

    // DEGREE
    ofstream dFile;
    dFile.open("degree.csv");
    int dVo[36] = {109,115,274,172,210,313,166,260,457,160,0,398,280,717,810,702,980,1115,515,509,457,1000,989,968,1463,1317,1625,549,815,55,1378,1503,1066,2074,1806,1901};
    int dVhp[36] = {109,115,274,172,210,313,166,260,457,160,0,398,280,662,810,702,965,1070,515,509,457,976,989,968,1463,1317,1610,501,786,517,1378,1503,1028,2074,1806,1820};
    for (int i = 0; i < 36; i++) {
        char* name;
        name = strcat("instanciasPRPP/DEGREE/D", i);
        char* file = strcat(name, noRPP);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::vector< vector<int> > sol  = graphAB.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(dVo[i], dVhp[i]);
        dHeur = pStd(dVo[i], vHeur);
        writeFile(strcat(file,"-salida.txt"), sol, vHeur);
        dFile << "D" << i << ", " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
    }
    dFile.close();

    // GRID
    ofstream grFile;
    grFile.open("grid.csv");
    int grVo[36] = {0,0,0,2,0,4,9,1,4,2,0,4,15,11,14,26,20,24,8,6,9,32,32,33,57,46,57,14,23,14,50,54,57,92,86,88};
    int grVhp[36] = {0,0,0,2,0,4,9,1,4,2,0,4,15,11,14,26,20,24,8,6,9,32,31,33,57,46,57,14,23,22,13,50,54,55,92,86,87};
    for (int i = 0; i < 36; i++) {
        char* name;
        name = strcat("instanciasPRPP/GRID/G", i);
        char* file = strcat(name, noRPP);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::vector< vector<int> > sol  = graphAB.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(grVo[i], grVhp[i]);
        dHeur = pStd(grVo[i], vHeur);
        writeFile(strcat(file,"-salida.txt"), sol, vHeur);
        grFile << "G" << i << ", " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
    }
    grFile.close();

    // RANDOM
    ofstream rFile;
    rFile.open("random.csv");
    int rVo[20] = {1742,4253,5638,18453,17316,398,12478,9405,14847,17405,7125,1493,32453,30732,27791,10533,4276,28462,26873};
    int rVhp[20] = {1742,4253,5638,18453,17316,398,12478,9405,14847,17405,7125,1493,30464,30732,27791,10533,4001,28462,26873};
    for (int i = 0; i < 20; i++) {
        char* name;
        name = strcat("instanciasPRPP/RANDOM/R", i);
        char* file = strcat(name, noRPP);
        Graph graph = readFile(file);
        timeStart = time(NULL);
        std::vector< vector<int> > sol  = graphAB.solvePRPP();
        timeEnd = time(NULL);
        tHeur = difftime(timeEnd, timeStart);
        // get standard deviations
        dvhp = pStd(rVo[i], rVhp[i]);
        dHeur = pStd(rVo[i], vHeur);
        writeFile(strcat(file,"-salida.txt"), sol, vHeur);
        grFile << "R" << i << ", " << vo << ", " << dvhp << ", " << dHeur << ", " << tHeur << std::endl;
    }
    rFile.close();

}

// % Standard deviation
float pStd(int vo, int vh) {
    return 100*((vo - vh)/vo);
}
