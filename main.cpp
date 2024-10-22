#include "adjacencymatrix.hpp"
#include <iostream>

#define NUMELEMENTS 20

void getInput(int* cities, int* tours, int* generations, double* percentGenerationMutation){
    std::cout << "Number of cities to run: ";    
    std::cin >> *cities;
    std::cout << "Number of tours: ";    
    std::cin >> *tours;
    std::cout << "Number of generations: ";    
    std::cin >> *generations;
    std::cout << "Percentage of Generations to mutate: ";    
    std::cin >> *percentGenerationMutation;
}

template<typename T>
void swap(T* a, T* b){
    T* tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
void print1Darr(T* arr, int size){
    std::cout << "[\n\t";
    for(int i = 0; i < size; i++){
        if (i == size - 1){
            std::cout << arr[i];
        } else {
            std::cout << arr[i] << ", ";
        }

        if ((i+1)%10 == 0 && i != size - 1){
            std::cout << "\n\t";
        }
    }
    std::cout << "\n]\n";
}

void perm1(int s[]){
    int m, k, p , q, i;

    m = NUMELEMENTS-2;
    while(s[m]>s[m+1]){
        m = m - 1;
    }

    k = NUMELEMENTS-1;
    while(s[m] > s[k]){
        k = k - 1;
    }
    swap(&m,&k);

    p = m + 1;
    q = NUMELEMENTS-1;
    while(p < q){
        swap(&p,&q);
        p++;
        q--;
    }

    print1Darr(s, NUMELEMENTS);
}

int main(){
    AdjacencyMatrix adjMatrix("res/distances.txt");
    // adjMatrix.print();

    // int cities, tours, generations;
    // double percentageGenerationMutation;
    // getInput(&cities, &tours, &generations, &percentageGenerationMutation);

    return 0;
}


/*

When your program runs, it will interactively get the following information from the user:

the number of cities to run

how many individual tours are in a given generation

how many generations to run
what percentage of a generation should be comprised of mutations
*/