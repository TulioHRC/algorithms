#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T, typename C>
void bubbleSort(T* vector, C start, C end) {
  for(C i = start; i < end; i++){
    for(C j = 1; j <= end - i; j++){
      if(vector[j] < vector[j-1]) swap(&vector[j-1], &vector[j]);
    }
  }
}

#endif