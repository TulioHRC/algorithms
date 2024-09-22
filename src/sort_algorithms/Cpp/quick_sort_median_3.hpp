#ifndef QUICK_M3_SORT_H
#define QUICK_M3_SORT_H

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
T median3 (T a, T b, T c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

// Partition pivot is the median of first, half and last positions
template <typename T, typename C>
void partition3(T * vector, C start, C end, C *i, C *j) {
  T pivotValue = median3(vector[start], vector[(start + end)/2], vector[end]);

  *i = start;
  *j = end;

  do {
    while(pivotValue > vector[*i]) (*i)++;
    while(pivotValue < vector[*j]) (*j)--;

    if(*i <= *j){
      swap(&vector[*i], &vector[*j]);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

template <typename T, typename C>
void quickSortMedian3(T* vector, C start, C end) {
  C i, j;
  partition3(vector, start, end, &i, &j);

  if(start < j) quickSortMedian3(vector, start, j); 
  if(i < end) quickSortMedian3(vector, i, end); 
}

#endif