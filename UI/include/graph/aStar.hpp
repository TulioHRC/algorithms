#ifndef A_STAR_H
#define A_STAR_H

#include "graph/adjMatrix.hpp"
#include "graph/adjList.hpp"
#include "graph/priorityQueue.hpp"

template <class T>
class AStar
{
    private:
        PriorityHeapQueue* priorityQueue;
        const T& data;
        int vertices;
        int toPoint;
        float * distancesToObjective;

    public:
        AStar(const T& data, int vertices, int subDivisions, int toPoint, float * distancesToObjective);
        ~AStar();

        bool isPossibleBetweenTwoPoints(int fromPoint); 
        float getDistanceBetweenTwoPoints(int fromPoint);

};


template <>
float AStar<AdjMatrix>::getDistanceBetweenTwoPoints(int fromPoint);

template <>
float AStar<AdjList>::getDistanceBetweenTwoPoints(int fromPoint);

template <>
bool AStar<AdjMatrix>::isPossibleBetweenTwoPoints(int fromPoint);

template <>
bool AStar<AdjList>::isPossibleBetweenTwoPoints(int fromPoint);

#endif