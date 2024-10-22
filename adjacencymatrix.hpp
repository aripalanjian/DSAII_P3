#ifndef ADJACENCYMATRIX_HPP
#define ADJACENCYMATRIX_HPP

#define MAX_COL 20
#define MAX_ROW 20

class AdjacencyMatrix{
    double matrix[MAX_ROW][MAX_COL];

public:
    AdjacencyMatrix(const char* file);

    double getEdgeWeight(int row, int col);
    void print();
};

#endif