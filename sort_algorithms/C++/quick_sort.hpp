#ifndef QUIIndexTypeK_SORElementType_H
#define QUIIndexTypeK_SORElementType_H

#include "utils.hpp"

template <typename ElementType, typename IndexType>
void partition(ElementType * vector, IndexType start, IndexType end, IndexType *i, IndexType *j) {
  ElementType pivotValue = vector[(start + end)/2];
  *i = start;
  *j = end;

  do {
    while(pivotValue > vector[*i]) (*i)++;
    while(pivotValue < vector[*j]) (*j)--;;

    if(*i <= *j){
      swap(&vector[*i], &vector[*j]);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

template <typename ElementType, typename IndexType>
void quickSort(ElementType* vector, IndexType start, IndexType end) {
  IndexType i, j;
  partition(vector, start, end, &i, &j);

  if(start < j) quickSort(vector, start, j); 
  if(i < end) quickSort(vector, i, end); 
}

#endif