#include "graph/aStar.hpp"
#include <iostream>

template <class T>
AStar<T>::AStar(const T &data, int vertices, int subDivisions, int toPoint, float *distancesToObjective) : data(data), vertices(vertices), toPoint(toPoint), distancesToObjective(distancesToObjective)
{
    this->priorityQueue = new PriorityHeapQueue(vertices + vertices * subDivisions, subDivisions);
}

template <class T>
AStar<T>::~AStar()
{
    delete this->priorityQueue;
}

template <class T>
float AStar<T>::getDistanceBetweenTwoPoints(int fromPoint)
{
    return -1;
}

template <class T>
bool AStar<T>::isPossibleBetweenTwoPoints(int fromPoint)
{
    return false;
}

// Matriz de Adjacência
template <>
float AStar<AdjMatrix>::getDistanceBetweenTwoPoints(int fromPoint)
{
    this->priorityQueue->insert({fromPoint,
                                 fromPoint,
                                 0.0,
                                 0.0});

    bool *visitedPoints = new bool[this->vertices]();
    data_t actualData;

    while (this->priorityQueue->isEmpty() == false && visitedPoints[this->toPoint] == false)
    {
        actualData = this->priorityQueue->remove();

        if (!visitedPoints[actualData.vertice])
        {

            for (int i = 0; i < this->vertices; i++)
            {
                if (!visitedPoints[i])
                {
                    if (this->data.getElement(actualData.vertice, i).cost != -1)
                    {
                        this->priorityQueue->insert({i,
                                                     actualData.vertice,
                                                     this->data.getElement(actualData.vertice, i).cost + this->distancesToObjective[i],
                                                     actualData.costAux + this->data.getElement(actualData.vertice, i).cost});
                    }
                }
            }
            visitedPoints[actualData.vertice] = true;
        }
    }

    delete[] visitedPoints;
    if (actualData.vertice == this->toPoint)
    {
        return actualData.costAux;
    }

    return -1;
}

template <>
bool AStar<AdjMatrix>::isPossibleBetweenTwoPoints(int fromPoint)
{
    float distance = getDistanceBetweenTwoPoints(fromPoint);
    if (distance == -1)
    {
        return false;
    }
    return true;
}

// Lista de Adjacência
template <>
float AStar<AdjList>::getDistanceBetweenTwoPoints(int fromPoint)
{
    this->priorityQueue->insert({fromPoint,
                                 fromPoint,
                                 0.0,
                                 0.0});

    bool *visitedPoints = new bool[this->vertices]();
    data_t actualData;

    while (this->priorityQueue->isEmpty() == false && visitedPoints[this->toPoint] == false)
    {
        actualData = this->priorityQueue->remove();
        listElement_t *neighbor = this->data.getNeighborhood(actualData.vertice);

        if (!visitedPoints[actualData.vertice])
        {

            while (neighbor != nullptr)
            {
                if (!visitedPoints[neighbor->vertice])
                {
                    if (neighbor->cost != -1)
                    {
                        this->priorityQueue->insert({neighbor->vertice,
                                                     actualData.vertice,
                                                     neighbor->cost + this->distancesToObjective[neighbor->vertice],
                                                     actualData.costAux + neighbor->cost});
                    }
                }

                neighbor = neighbor->nextElement;
            }

            visitedPoints[actualData.vertice] = true;
        }
    }

    delete[] visitedPoints;
    if (actualData.vertice == this->toPoint)
    {
        return actualData.costAux;
    }

    return -1;
}

template <>
bool AStar<AdjList>::isPossibleBetweenTwoPoints(int fromPoint)
{
    float distance = getDistanceBetweenTwoPoints(fromPoint);
    if (distance == -1)
    {
        return false;
    }
    return true;
}

template class AStar<AdjMatrix>;
template class AStar<AdjList>;
