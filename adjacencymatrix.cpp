#include "adjacencymatrix.hpp"
#include <fstream>
#include <iostream>

AdjacencyMatrix::AdjacencyMatrix(const char* file){
    std::ifstream in(file);

    std::string val;
    for (int i = 0; i < MAX_ROW; i++){
        for (int j = 0; j < MAX_COL; j++){
            if (i == j){
                matrix[i][j] = 0;
            } else {
                std::getline(in, val);
                matrix[i][j] = std::stod(val);
            }
        }
    }
}

double AdjacencyMatrix::getEdgeWeight(int row, int col){
    return matrix[row][col];
}

void AdjacencyMatrix::print(){
    for (int i = 0; i < MAX_ROW; i++){
        for (int j = 0; j < MAX_COL; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}