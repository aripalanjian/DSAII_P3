/***************************************************************
  Student Name: Ari Palanjian
  File Name: genetic.hpp
  Project 3

  Class that implements a Genetic like algorithm to determine the
    lowest cost of a path starting and ending at 0.
***************************************************************/
#ifndef GENETIC_HPP
#define GENETIC_HPP

#include "adjacencymatrix.hpp"
#include <time.h>

#define MAX_CITIES 20
#define MAX_COST 100000000000000

class Genetic{
    int nfact = 1;
    double bestCost = MAX_COST;
    int n; //Number of cities
    int count = 1;
    int numGenerations;
    int percentMutations;
    int tours;
    double bruteBest;    
    time_t computationTimeS;
    long computationTimeNS;

    int* s;
    int** generation;
    int** elite;
    int** mutations;
    int* bestArr;    
    
    AdjacencyMatrix* matrix;

    void initArrays();
    void calculateFactorial();
    void populate();
    void swap(int i, int j);
    void perm1(int s[]);
    void partitionElites(int j, int k, int partitionA, int partitionB, int a[], int b[]);
    bool containsCity(int partitionA, int partitionB, int a[], int b[]);
    int crossover(int maxCrossover);
    void mutate(int s[]);
    void generateTour();
    
    double evaluateCost(int s[]);
    void evaluateGenerationCost();  
    void printS(int s[]);
public:
    Genetic(int length, int tours, int numGenerations, int percentMutations, double bruteBest);
    ~Genetic();
    void run();
    int* getS(){return bestArr;}
    double getBest(){return bestCost;}
    time_t getComputationTimeS(){return computationTimeS;}
    long getComputationTimeNS(){return computationTimeNS;}
};

#endif