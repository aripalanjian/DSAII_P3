/***************************************************************
  Student Name: Ari Palanjian
  File Name: genetic.cpp
  Project 3

  Member function definitions for class Genetic
***************************************************************/
#include "genetic.hpp"
#include <iostream>

Genetic::Genetic(int length, int tours, int numGenerations, int percentMutations, double bruteBest){
    srand(0);
    n = length;
    this->tours = tours; 
    this->numGenerations = numGenerations;
    this->percentMutations = percentMutations;
    this->bruteBest = bruteBest;

    initArrays();
    calculateFactorial();
    populate();
}

Genetic::~Genetic(){
    delete [] s;
    // delete elites
    for (int i = 0; i < (tours/10 + 2); i++){
        delete [] elite[i];
    }
    delete [] elite;
    //delete generation
    for(int i = 0; i < tours; i++){
        delete [] generation[i];
    }
    delete [] generation;
    //delete mutations
    for (int i = 0; i < tours*percentMutations/100; i++){
        delete [] mutations[i];
    }
    delete [] mutations;
    delete [] bestArr;
    delete matrix;
}

void Genetic::initArrays() {
    s = new int[n+1];

    generation = new int*[tours];
    for(int i = 0; i < tours; i++){
        generation[i] = new int[n+1];
    }

    elite = new int*[tours/10 + 2];
    for (int i = 0; i < (tours/10 + 2); i++){
        elite[i] = new int[n+1];
    }

    mutations = new int*[tours*percentMutations/100];
    for (int i = 0; i < tours*percentMutations/100; i++){
        mutations[i] = new int[n+1];
    }

    bestArr = new int[n+1];
    matrix = new AdjacencyMatrix("res/distances.txt");
}

void Genetic::calculateFactorial(){
    int i = 1;
    while(i<=n){
        nfact *= i++;
    }
}

void Genetic::populate(){
    int i = 0;
    for (i = 0; i < n; i++){
        s[i] = i+1;
    }
    s[i] = 0;
    evaluateCost(s);
}

void Genetic::swap(int a, int b){
    int tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}

void Genetic::printS(int s[]){
    using std::cout;
    cout << 0 << " ";
    for(int i = 0; i <= n; i++){
        cout << s[i] << " ";
    }
    cout << "\n";
}

void Genetic::perm1(int s[]){
    int NUMELEMENTS = n;
    int m, k, p , q;

    m = NUMELEMENTS-2;
    while(s[m]>s[m+1]){
        m = m - 1;
    }

    k = NUMELEMENTS-1;
    while(s[m] > s[k]){
        k = k - 1;
    }
    swap(m,k);

    p = m + 1;
    q = NUMELEMENTS-1;
    while(p < q){
        swap(p,q);
        p++;
        q--;
    }
}

double Genetic::evaluateCost(int s[]){
    double cost = matrix->getEdgeWeight(0,s[0]);
    int i;
    for (i = 0; i < n; i++){
        cost += matrix->getEdgeWeight(s[i],s[i+1]);
    }
    if (cost < bestCost) {
        bestCost = cost;
        for(int i = 0; i < n + 1; i++){
            bestArr[i] = s[i];
        }
    }

    return cost;
}

void Genetic::evaluateGenerationCost(){

    double cost[tours];
    double bestGenCost = MAX_COST;
    double prevBest, nextBest;
    int best[tours/10 + 2];
    for (int i = 0; i < tours; i++){
        cost[i] = evaluateCost(generation[i]);
        if (cost[i] < bestGenCost) {
            bestGenCost = cost[i];
        }
    }
    
    for (int j = 0; j < tours; j++){
        if (cost[j] == bestGenCost) {
            best[0] = j;
            prevBest = bestGenCost;
            break;
        }
    }
    int i = 1;
    int index = 0;
    bestGenCost = MAX_COST;
    while (i < (tours/10 + 2)){
        for (int j = 0; j < tours; j++){
            if (cost[j] < bestGenCost && cost[j] > prevBest) {
                bestGenCost = cost[j];
                nextBest = cost[j];
                index = j;
            }
        }
        best[i] = index;
        prevBest = nextBest;
        bestGenCost = MAX_COST;
        i++;
    }

    for (int i = 0; i < (tours/10 + 2); i++) {
        for(int j = 0; j < n+1; j++){
            elite[i][j] = generation[best[i]][j];
        }
    }
}

void Genetic::partitionElites(int j, int k, int partitionA, int partitionB, int a[], int b[]){
    
    for(int i = 0; i < n; i++){
        if (i < partitionA) {
            a[i] = elite[j][n-partitionA + i];
        } else {
            b[i] = elite[k][i];
        }
    }
}

bool Genetic::containsCity(int partitionA, int partitionB, int a[], int b[]){
    for (int i = partitionB; i < n; i++){
        for(int j = partitionA; j < n; j++){
            if (b[i] == a[j]) {
                return true;
            }
        }
    }

    return false;
    
}

int Genetic::crossover(int maxCrossover){
    int i = 0;
    int partitionA = n/2, partitionB = n/2;
    if(n%2 != 0){
        partitionA = n/2;
        partitionB = n/2 + 1;
    }
    int a[partitionA], b[partitionB];

    while (i < maxCrossover) {
        for(int j = 0; j < (tours/10 + 2); j++) {
            for(int k = 0; k < (tours/10 + 2); k++){
                if (j != k) {
                    partitionElites(j, k, partitionA, partitionB, a, b);
                    if (!containsCity(partitionA, partitionB, a, b)) {
                        for(int l = 0; l < n+1; l++){                             
                            if (i < partitionA) {
                                mutations[i][l] = a[l];
                            } else {
                                mutations[i][l] = b[l-partitionA];
                            }
                        }
                        i++;
                    }
                }
            }
        }
    }

    return i;
}

void Genetic::mutate(int s[]){
    int numSwap = rand()%4 + 1;
    for (int i = 0; i < numSwap; i++){
        int a = rand()%n, b = rand()%n;
        while(a==b){
            a = rand()%n;
            b = rand()%n;
        }
        int tmp = s[a];
        s[a] = s[b];
        s[b] = tmp;
    }
}

void Genetic::generateTour(){
    // for(int i = 0; i < tours*percentMutations/100; i++){
    //     for(int j = 0; j < n + 1; j++){
    //         mutations[i][j] = elite[0][j];
    //     }
    // }
    int i = 0;
    int k = 0;
    while (i < tours*percentMutations/100){
        for(int j = 0; j < n + 1; j++){
            if (k == tours/10 + 2){
                k = 0;
            }
            mutations[i][j] = elite[k][j];
        }
        i++;
        k++;
    }
    i = 0;
    for(i = 0; i < tours*percentMutations/100; i++){
        mutate(mutations[i]);
        for(int j = 0; j < n + 1; j++){
            generation[i][j] = mutations[i][j];
        }
    }
    for (int j = 0; j < n + 1; j++){
        generation[i][j] = elite[0][j];
        s[j] = elite[0][j];
    }
    i++;
    for(i = i; i < tours; i++){
        perm1(s);
        for(int j = 0; j < n+1; j++){
            generation[i][j] = s[j];
        }
    }
    evaluateGenerationCost();

}

void Genetic::run(){
    struct timespec start;
    struct timespec finish;

    int genCount = 0;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int i = 0; i < tours; i++){
        perm1(s);
        for(int j = 0; j < n+1; j++){
            generation[i][j] = s[j];
        }
    }
    genCount++;
    evaluateGenerationCost();
    if (!(bestCost/bruteBest < 1.20)){
        for(int i = 0; i < numGenerations - 1; i++){
            generateTour();
            genCount++;
            if (bestCost/bruteBest < 1.20){
                break;
            }
        }
    }
    clock_gettime(CLOCK_REALTIME, &finish);

    if (start.tv_nsec > finish.tv_nsec){
        computationTimeS = finish.tv_sec - 1 - start.tv_sec;
        computationTimeNS = (long)1e9 + finish.tv_nsec - start.tv_nsec;
    } else {
        computationTimeS = finish.tv_sec - start.tv_sec;
        computationTimeNS = finish.tv_nsec - start.tv_nsec;
    }
}