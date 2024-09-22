#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

template <typename T, typename C>
void insertionSort(T* vector, C start, C end) {
  C behindPos, aux;

  for (C pos = start; pos < end; pos++){
    aux = vector[pos + 1];
    behindPos = pos;
    while((behindPos >= start) && (aux < vector[behindPos])){
      vector[behindPos + 1] = vector[behindPos];
      behindPos--;
    }

    vector[behindPos + 1] = aux;
  }
}

#endif