#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include "insertion_sort.hpp"

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

// BucketSort implementation executing an insertion sort in each bucket (with n buckets -> size of the end - start) and setting max and min of the vector before running the algorithm
template <typename T, typename C>
void bucketSort(T* vector, C start, C end) {
  T max = vector[start];
  T min = vector[start];
  for(C i = start + 1; i <= end; i++){
    if(max < vector[i]) max = vector[i];
    else {
      if (min > vector[i]) min = vector[i];
    }
  }

  int countSizeOfBuckets[end-start+1];
  int countSizeOfBucketsCopy[end-start+1];
  memset(countSizeOfBuckets, 0, (end-start+1) * sizeof(int));
  memset(countSizeOfBucketsCopy, 0, (end-start+1) * sizeof(int));

  C bucketInterval = (max-min) / (end-start+1) + 1;

  for(C i = start; i <= end; i++){
    C bucketNum = (vector[i]-min) / (bucketInterval);
    countSizeOfBuckets[bucketNum]++;
    countSizeOfBucketsCopy[bucketNum]++;
  }

  T* buckets[end-start+1];
  for(C i = 0; i < end-start+1; i++){
    buckets[i] = new T[countSizeOfBuckets[i]];
  }

  for(C i = start; i <= end; i++){
    C bucketNum = (vector[i]-min) / (bucketInterval);
    if(countSizeOfBuckets[bucketNum] > 0){
      buckets[bucketNum][countSizeOfBuckets[bucketNum]-1] = vector[i];
      countSizeOfBuckets[bucketNum]--;
    }
  }

  C pos = 0;
  for(C i = 0; i < end-start+1; i++){
    insertionSort(buckets[i], 0, countSizeOfBucketsCopy[i] - 1);
    for(C j = 0; j < countSizeOfBucketsCopy[i]; j++){
      vector[pos] = buckets[i][j];
      pos++;
    }
  }
}

#endif