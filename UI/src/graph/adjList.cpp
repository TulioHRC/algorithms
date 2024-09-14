#include "graph/adjList.hpp"

AdjList::AdjList(int vertices)
{
    this->list = new listElement_t*[vertices];

    for(int i = 0; i < vertices; i++)
    {
        this->list[i] = nullptr;
    }
}

AdjList::~AdjList()
{
    delete[] list;
}

void AdjList::insert(int cost, int fromPos, int toPos)
{
    if(this->list[fromPos] == nullptr)
    {
        this->list[fromPos] = new listElement_t({
            toPos,
            cost,
            false,
            nullptr
        });
    } else { 
        listElement_t* element = this->list[fromPos];
        while(element->nextElement != nullptr){
            if(element->vertice == toPos)
            {
                element->cost = cost;
                break;
            }
            element = element->nextElement;
        }
        if(element->vertice != toPos){
            element->nextElement = new listElement_t({
                toPos,
                cost,
                false,
                nullptr
            });
        }
    }
}

void AdjList::insertPortal(int fromPos, int toPos)
{
    if(this->list[fromPos] == nullptr)
    {
        this->list[fromPos] = new listElement_t({
            toPos,
            -1,
            true,
            nullptr
        });
    } else { 
        listElement_t* element = this->list[fromPos];
        while(element->nextElement != nullptr){
            if(element->vertice == toPos)
            {
                element->hasPortal = true;
                break;
            }
            element = element->nextElement;
        }
        if(element->vertice != toPos){
            element->nextElement = new listElement_t({
                toPos,
                -1,
                true,
                nullptr
            });
        }
    }
}

listElement_t* AdjList::getNeighborhood(int pos) const 
{
    return this->list[pos];
}
