/***************************************************************
  Student Name: Ari Palanjian
  File Name: brute.hpp
  Project 3

  Class that implements a brute force method to determine the
    lowest cost of a path starting and ending at 0.
***************************************************************/
#ifndef BRUTE_HPP
#define BRUTE_HPP

#include "adjacencymatrix.hpp"
#include <time.h>

#define MAX_CITIES 20
#define MAX_COST 100000000000000

class Brute{
    int nfact = 1;
    double bestCost = MAX_COST;
    int n; //Number of cities
    int count = 1;
    time_t computationTimeS;
    long computationTimeNS;

    int* s;
    int* bestArr;

    AdjacencyMatrix* matrix;

    void calculateFactorial();
    void populate();
    
    void swap(int i, int j);
    void perm1(int s[]);
    void evaluateCost();
    
    void printS(int s[]);
public:
    Brute(int length);
    ~Brute();
    void run();
    int* getS(){return bestArr;}
    double getBest(){return bestCost;}
    time_t getComputationTimeS(){return computationTimeS;}
    long getComputationTimeNS(){return computationTimeNS;}
};

#endif