/***************************************************************
  Student Name: Ari Palanjian
  File Name: brute.cpp
  Project 3

  Member function definitions for class Brute
***************************************************************/
#include "brute.hpp"
#include <iostream>

Brute::Brute(int length){
    n = length;
    s = new int[n+1];
    bestArr = new int[n+1];
    matrix = new AdjacencyMatrix("res/distances.txt");
    calculateFactorial();
    populate();
}

Brute::~Brute(){
    delete [] s;
    delete [] bestArr;
    delete matrix;
}

void Brute::calculateFactorial(){
    int i = 1;
    while(i<=n){
        nfact *= i++;
    }
}

void Brute::populate(){
    int i = 0;
    for (i = 0; i < n; i++){
        s[i] = i+1;
    }
    s[i] = 0;
    evaluateCost();
}

void Brute::swap(int a, int b){
    int tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}

void Brute::printS(int s[]){
    using std::cout;
    cout << 0 << " ";
    for(int i = 0; i <= n; i++){
        cout << s[i] << " ";
    }
}

void Brute::perm1(int s[]){
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

void Brute::evaluateCost(){
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
}

void Brute::run(){
    struct timespec start;
    struct timespec finish;

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 1; i < nfact; i++){
        perm1(s);
        evaluateCost();
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