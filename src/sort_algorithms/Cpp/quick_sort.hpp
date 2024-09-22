#ifndef QUICK_SORT_H
#define QUICK_SORT_H

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T, typename C>
void partition(T * vector, C start, C end, C *i, C *j) {
  T pivotValue = vector[(start + end)/2];
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

template <typename T, typename C>
void quickSort(T* vector, C start, C end) {
  C i, j;
  partition(vector, start, end, &i, &j);

  if(start < j) quickSort(vector, start, j); 
  if(i < end) quickSort(vector, i, end); 
}

#endif