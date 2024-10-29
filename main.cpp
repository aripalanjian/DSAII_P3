/***************************************************************
  Student Name: Ari Palanjian
  File Name: main.cpp
  Project 3

  Driver program to simulate Traveling Salesman Problem
***************************************************************/
#include "brute.hpp"
#include "genetic.hpp"
#include <iostream>

#include <time.h>

#define NUMELEMENTS 20

void getInput(int* cities, int* tours, int* generations, int* percentGenerationMutation){
    std::cout << "Number of cities to run: ";    
    std::cin >> *cities;
    std::cout << "Number of tours: ";    
    std::cin >> *tours;
    std::cout << "Number of generations: ";    
    std::cin >> *generations;
    std::cout << "Percentage of Generations to mutate: ";    
    std::cin >> *percentGenerationMutation;
}

void ouput(int cities, double bruteBest, time_t computationTimeSBrute, long computationTimeNSBrute,
    double genBest, time_t computationTimeSGen, long computationTimeNSGen){
    using std::cout;
    cout << "Number of cities: " << cities << "\n";
    cout << "Brute force optimal: " << bruteBest << "\n";
    cout << "Brute force time: " << computationTimeSBrute << "." << computationTimeNSBrute << "s\n";
    cout << "Genetic optimal: " << genBest << "\n";
    cout << "Genetic time: " << computationTimeSGen << "." << computationTimeNSGen << "s\n";
    cout << "Percent optimal: " << int(genBest/bruteBest * 100) << "\n";
}

int main(){
    int cities, tours, generations, percentageGenerationMutation;
    getInput(&cities, &tours, &generations, &percentageGenerationMutation);

    Brute b = Brute(cities);
    b.run();
    double bruteBest = b.getBest();

    Genetic g = Genetic(cities, tours, generations, percentageGenerationMutation, bruteBest);
    g.run();

    ouput(cities, bruteBest, b.getComputationTimeS(), b.getComputationTimeNS(),
        g.getBest(), g.getComputationTimeS(), g.getComputationTimeNS());

    return 0;
}