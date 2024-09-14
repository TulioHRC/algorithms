#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct point {
  int x;
  int y;
};

struct data_t {
    int vertice;
    int lastVertice;
    double cost;
    double costAux;
};

class PriorityHeapQueue
{

    public:
        PriorityHeapQueue(int maxSize, int subDivisions);
        ~PriorityHeapQueue();

        void insert(data_t);
        data_t remove();

        bool isEmpty();

    private:
        int getAncestor(int pos);
        int getSucessorLeft(int pos);
        int getSucessorRight(int pos);
        long long getIndex(data_t x);

        int size;
        int subDivisions;
        data_t* data;
        long long* indexes;

        int getPosToInsert(data_t);
        void updateValue(data_t, int pos);

        void HeapifyFromDown(int pos);
        void HeapifyFromUp(int pos);

};

#endif