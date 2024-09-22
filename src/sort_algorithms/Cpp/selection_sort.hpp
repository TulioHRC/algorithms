#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T, typename C>
void selectionSort(T* vector, C start, C end) {
  C actualMinPos;

  for (C pos = start; pos < end; pos++){
    actualMinPos = pos;
    for (C i = pos + 1; i <= end; i ++){
      if (vector[i] < vector[actualMinPos]){
        actualMinPos = i;
      }
    }
    if(actualMinPos != pos) swap(&vector[pos], &vector[actualMinPos]);
  }
}

#endif