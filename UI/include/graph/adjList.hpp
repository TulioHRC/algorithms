#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <string>

struct listElement_t {
    int vertice;
    int cost;
    listElement_t* nextElement;
};

class AdjList 
{

    private:
        listElement_t ** list;

    public:
        AdjList(int vertices);
        ~AdjList();

        void insert(int cost, int fromPos, int toPos);
        void insertPortal(int fromPos, int toPos);
        listElement_t * getNeighborhood(int pos) const;        

};

AdjList readFileToAdjList(std::string filename);

#endif