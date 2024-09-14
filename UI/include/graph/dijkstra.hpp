#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph/adjMatrix.hpp"
#include "graph/adjList.hpp"
#include "graph/priorityQueue.hpp"

template <class T>
class Dijkstra 
{
    private:
        PriorityHeapQueue* priorityQueue;
        const T& data;
        int vertices;

    public:
        Dijkstra(const T& data, int vertices, int subDivisions);
        ~Dijkstra();

        float getDistanceBetweenTwoPoints(int fromPoint, int toPoint);
        bool isPossibleBetweenTwoPoints(int fromPoint, int toPoint); 
};

template <>
float Dijkstra<AdjMatrix>::getDistanceBetweenTwoPoints(int fromPoint, int toPoint);

template <>
float Dijkstra<AdjList>::getDistanceBetweenTwoPoints(int fromPoint, int toPoint);

template <>
bool Dijkstra<AdjMatrix>::isPossibleBetweenTwoPoints(int fromPoint, int toPoint);

template <>
bool Dijkstra<AdjList>::isPossibleBetweenTwoPoints(int fromPoint, int toPoint);

#endif
