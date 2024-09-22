#ifndef MERGE_SORT_H
#define MERGE_SORT_H

template <typename T, typename C>
void merge(T * vector, C start, C mid, C end){
  T * result = new T[end - start + 1];
  C i = 0;
  C j = 0;
  C k = 0;
  while (i < (mid - start + 1) && j < (end - mid)) {
    if (vector[start + i] < vector[j + mid + 1]) {
      result[k] = vector[start + i];
      i++;
    } else {
      result[k] = vector[j + mid + 1];
      j++;
    }
    k++;
  }

  if (k < (end - start + 1)) {
    for(; i < (mid - start + 1); i++) {
      result[k] = vector[start + i];
      k++;
    }
    for(; j < (end - mid); j++) {
      result[k] = vector[mid + 1 + j];
      k++;
    }
  }

  for(C i = start; i <= end; i++){
    vector[i] = result[i-start];
  }
}

template <typename T, typename C>
void mergeSort(T* vector, C start, C end) {
  if(start < end){
    C mid = (start + end)/2;
    mergeSort(vector, start, mid);
    mergeSort(vector, mid + 1, end);
    merge(vector, start, mid, end);
  }
}

#endif