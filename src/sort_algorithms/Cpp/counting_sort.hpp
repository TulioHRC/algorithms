#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

template <typename T, typename C>
void countingSort(T* vector, C start, C end) {
  T max = vector[start];
  T min = vector[start];
  for(C i = start + 1; i <= end; i++){
    if(max < vector[i]) max = vector[i];
    else {
      if (min > vector[i]) min = vector[i];
    }
  }

  C count[max - min + 2];
  memset(count, 0, (max-min+2)*sizeof(C));

  for(C i = start; i <= end; i++){
    count[vector[i] - min]++;
  }

  C pos = 0;
  for(C i = 0; i <= (max-min+1); i++){
    for(C j = count[i]; count[i] > 0; j--){
      count[i]--;
      vector[pos] = i+min;
      pos++; 
    }
  }
}

#endif