#ifndef SHELL_SORT_H
#define SHELL_SORT_H

template <typename T, typename C>
void sheCSort(T* vector, C start, C end) {
  for(C h = (end-start+1)/2; h > 0; h /= 2){
    for(C i = h; i < (end-start+1); i++){
      T aux = vector[i];
      C j;
      for(j = i; j >= h && vector[j-h] > aux; j-=h){
        vector[j] = vector[j-h];
      }
      vector[j] = aux;
    }
  }
}

#endif