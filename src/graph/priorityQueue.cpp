#include "graph/priorityQueue.hpp"
#include "stdexcept"
#include <cstring>

PriorityHeapQueue::PriorityHeapQueue(int maxSize, int subDivisions) : subDivisions(subDivisions)
{
    data = new data_t[maxSize];
    indexes = new long long[maxSize];
    std::memset(indexes, -1, maxSize * sizeof(long long));
    size = 0;
}

PriorityHeapQueue::~PriorityHeapQueue()
{
    delete[] data;
    delete[] indexes;
}

void PriorityHeapQueue::insert(data_t x)
{
    long long index = getIndex(x);
    long long indexPosition = this->indexes[index];
    if(indexPosition != -1)
    {
        if(x.cost < this->data[indexPosition].cost)
        {
            this->data[indexPosition] = x;

            HeapifyFromDown(indexPosition);
            HeapifyFromUp(indexPosition);
        }
    } else
    {
        data[size] = x;
        this->indexes[index] = size;

        HeapifyFromDown(size);

        size++;
    }
}

data_t PriorityHeapQueue::remove()
{
    if(isEmpty())
    {
        throw std::out_of_range("Heap is empty, no element can be removed!");
    }

    data_t removedElement = data[0];

    this->indexes[getIndex(removedElement)] = -1;

    data[0] = data[size-1];

    HeapifyFromUp(0);

    size--;
    return removedElement;
}

bool PriorityHeapQueue::isEmpty()
{
    return (size == 0) ? true : false;
}

int PriorityHeapQueue::getAncestor(int pos)
{
    return (pos - 1) / 2;
}

int PriorityHeapQueue::getSucessorLeft(int pos)
{
    return 2 * pos + 1;
}

int PriorityHeapQueue::getSucessorRight(int pos)
{
    return 2 * pos + 2;
}

long long PriorityHeapQueue::getIndex(data_t x)
{
    return x.vertice * this->subDivisions + x.vertice;
}

void PriorityHeapQueue::HeapifyFromDown(int pos)
{
    int ancestorPos = getAncestor(pos);
    if(data[ancestorPos].cost > data[pos].cost){
        data_t aux = data[pos];

        this->indexes[getIndex(data[pos])] = ancestorPos;
        this->indexes[getIndex(data[ancestorPos])] = pos;

        data[pos] = data[ancestorPos];
        data[ancestorPos] = aux;

        HeapifyFromDown(ancestorPos);
    }
}

void PriorityHeapQueue::HeapifyFromUp(int pos)
{
    int left, right;
    left = getSucessorLeft(pos);
    right = getSucessorRight(pos);
    int smallest = pos;

    if(left < size)
    {
        smallest = (data[left].cost < data[smallest].cost) ? left : smallest;
    }

    if(right < size)
    {
        smallest = (data[right].cost < data[smallest].cost) ? right : smallest;
    }

    if(pos != smallest)
    {
        data_t aux = data[pos];

        this->indexes[getIndex(data[pos])] = smallest;
        this->indexes[getIndex(data[smallest])] = pos;

        data[pos] = data[smallest];
        data[smallest] = aux;
        HeapifyFromUp(smallest);
    }
}
