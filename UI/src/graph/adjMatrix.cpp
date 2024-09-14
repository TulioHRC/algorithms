#include "graph/adjMatrix.hpp"

AdjMatrix::AdjMatrix(int size)
{
    this->matrix = new element_t*[size];

    for(int i = 0; i < size; i++){
        this->matrix[i] = new element_t[size];
        for(int j = 0; j < size; j++){
            this->matrix[i][j] = element_t({-1, false});
        }
    }
}

AdjMatrix::~AdjMatrix()
{
    delete[] matrix;
}

void AdjMatrix::insert(int cost, int fromPos, int toPos)
{
    this->matrix[fromPos][toPos].cost = cost;
}

void AdjMatrix::insertPortal(int fromPos, int toPos)
{
    this->matrix[fromPos][toPos].hasPortal = true;
}

element_t AdjMatrix::getElement(int row, int column) const
{
    return this->matrix[row][column];
}