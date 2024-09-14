#include "graph/dijkstra.hpp"

template <class T>
Dijkstra<T>::Dijkstra(const T &data, int vertices, int subDivisitions) : data(data), vertices(vertices)
{
    this->priorityQueue = new PriorityHeapQueue(vertices + vertices * subDivisitions, subDivisitions);
}

template <class T>
Dijkstra<T>::~Dijkstra()
{
    delete this->priorityQueue;
}

// Other types
template <class T>
float Dijkstra<T>::getDistanceBetweenTwoPoints(int fromPoint, int toPoint)
{
    return -1;
}

template <class T>
bool Dijkstra<T>::isPossibleBetweenTwoPoints(int fromPoint, int toPoint)
{
    return false;
}

template <>
float Dijkstra<AdjMatrix>::getDistanceBetweenTwoPoints(int fromPoint, int toPoint)
{
    this->priorityQueue->insert({fromPoint,
                                 fromPoint,
                                 0.0});

    bool *visitedPoints = new bool[this->vertices]();
    data_t actualData;

    while (this->priorityQueue->isEmpty() == false && visitedPoints[toPoint] == false)
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
                                                     actualData.cost + this->data.getElement(actualData.vertice, i).cost});
                    }
                }
            }
            visitedPoints[actualData.vertice] = true;
        }
    }

    delete[] visitedPoints;
    if (actualData.vertice == toPoint)
    {
        return actualData.cost;
    }

    return -1;
}

template <>
bool Dijkstra<AdjMatrix>::isPossibleBetweenTwoPoints(int fromPoint, int toPoint)
{
    float distance = getDistanceBetweenTwoPoints(fromPoint, toPoint);
    if (distance == -1)
    {
        return false;
    }
    return true;
}

template <>
float Dijkstra<AdjList>::getDistanceBetweenTwoPoints(int fromPoint, int toPoint)
{
    this->priorityQueue->insert({fromPoint,
                                 fromPoint,
                                 0.0});

    bool *visitedPoints = new bool[this->vertices]();
    data_t actualData;

    while (this->priorityQueue->isEmpty() == false && visitedPoints[toPoint] == false)
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
                                                     actualData.cost + neighbor->cost});
                    }
                }

                neighbor = neighbor->nextElement;
            }

            visitedPoints[actualData.vertice] = true;
        }
    }

    delete[] visitedPoints;
    if (actualData.vertice == toPoint)
    {
        return actualData.cost;
    }

    return -1;
}

template <>
bool Dijkstra<AdjList>::isPossibleBetweenTwoPoints(int fromPoint, int toPoint)
{
    float distance = getDistanceBetweenTwoPoints(fromPoint, toPoint);
    if (distance == -1)
    {
        return false;
    }
    return true;
}

template class Dijkstra<AdjMatrix>;
template class Dijkstra<AdjList>;
