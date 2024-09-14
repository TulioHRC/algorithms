#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <string>

struct element_t {
    int cost;
};

class AdjMatrix 
{

    private:
        element_t ** matrix;

    public:
        AdjMatrix(int size);
        ~AdjMatrix();

        void insert(int cost, int fromPos, int toPos);
        void insertPortal(int fromPos, int toPos);
        element_t getElement(int row, int column) const;

};

AdjMatrix readFileToAdjMatrix(std::string filename);

#endif