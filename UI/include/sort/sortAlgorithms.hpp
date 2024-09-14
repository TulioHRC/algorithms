#ifndef SORT_ALGORITHM
#define SORT_ALGORITHM

#include <time.h>
#include <vector>
#include <iostream>

typedef long long ll;

template <typename T>
void swap(T *xp, T *yp){
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Classic bubbleSort implementation
template <typename T>
void bubbleSort(T* vector, ll start, ll end) {
  for(ll i = start; i < end; i++){
    for(ll j = 1; j <= end - i; j++){
      if(vector[j] < vector[j-1]) swap(&vector[j-1], &vector[j]);
    }
  }
}

// Classic insertionSort implementation
template <typename T>
void insertionSort(T* vector, ll start, ll end) {
  ll behindPos, aux;

  for (ll pos = start; pos < end; pos++){
    aux = vector[pos + 1];
    behindPos = pos;
    while((behindPos >= start) && (aux < vector[behindPos])){
      vector[behindPos + 1] = vector[behindPos];
      behindPos--;
    }

    vector[behindPos + 1] = aux;
  }
}

// Classic insertionSort implementation
template <typename T>
void selectionSort(T* vector, ll start, ll end) {
  ll actualMinPos;

  for (ll pos = start; pos < end; pos++){
    actualMinPos = pos;
    for (ll i = pos + 1; i <= end; i ++){
      if (vector[i] < vector[actualMinPos]){
        actualMinPos = i;
      }
    }
    if(actualMinPos != pos) swap(&vector[pos], &vector[actualMinPos]);
  }
}

// Partition pivot being the half position in the vector
template <typename T>
void partition(T * vector, ll start, ll end, ll *i, ll *j) {
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

// Classic quickSort implementation with pivot being the half position in the vector
template <typename T>
void quickSort(T* vector, ll start, ll end) {
  ll i, j;
  partition(vector, start, end, &i, &j);

  if(start < j) quickSort(vector, start, j); 
  if(i < end) quickSort(vector, i, end); 
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
template <typename T>
void partition3(T * vector, ll start, ll end, ll *i, ll *j) {
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

// QuickSort implementation with pivot being the median of first, half and last positions in the vector
template <typename T>
void quickSortMedian3(T* vector, ll start, ll end) {
  ll i, j;
  partition3(vector, start, end, &i, &j);

  if(start < j) quickSortMedian3(vector, start, j); 
  if(i < end) quickSortMedian3(vector, i, end); 
}

// QuickSort implementation with pivot being the median of first, half and last positions in the vector and using insertion sort when the remaining vector it's <= 50 elements
template <typename T>
void quickSortMedian3WithInsertionSort(T* vector, ll start, ll end) {
  ll i, j;
  
  partition3(vector, start, end, &i, &j);

  if(start < j){
    if(j - start > 50) quickSortMedian3WithInsertionSort(vector, start, j);
    else insertionSort(vector, start, j);
  }
  if(i < end){
    if(end - i > 50) quickSortMedian3WithInsertionSort(vector, i, end);
    else insertionSort(vector, i, end);
  }
}

// Merges (start)->(mid-1) vector with (mid)->(end) vector
template <typename T>
void merge(T * vector, ll start, ll mid, ll end){
  T * result = new T[end - start + 1];
  ll i = 0;
  ll j = 0;
  ll k = 0;
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

  for(ll i = start; i <= end; i++){
    vector[i] = result[i-start];
  }
}

// Classic mergeSort implementation
template <typename T>
void mergeSort(T* vector, ll start, ll end) {
  if(start < end){
    ll mid = (start + end)/2;
    mergeSort(vector, start, mid);
    mergeSort(vector, mid + 1, end);
    merge(vector, start, mid, end);
  }
}

// Classic shellSort implementation of Donald Shell, 1959
template <typename T>
void shellSort(T* vector, ll start, ll end) {
  for(ll h = (end-start+1)/2; h > 0; h /= 2){
    for(ll i = h; i < (end-start+1); i++){
      T aux = vector[i];
      ll j;
      for(j = i; j >= h && vector[j-h] > aux; j-=h){
        vector[j] = vector[j-h];
      }
      vector[j] = aux;
    }
  }
}

// Classical countingSort implementation (setting max and min of the vector, to save some memory)
template <typename T>
void countingSort(T* vector, ll start, ll end) {
  // Find max and minimum
  T max = vector[start];
  T min = vector[start];
  for(ll i = start + 1; i <= end; i++){
    if(max < vector[i]) max = vector[i];
    else {
      if (min > vector[i]) min = vector[i];
    }
  }

  ll count[max - min + 2];
  memset(count, 0, (max-min+2)*sizeof(ll));

  for(ll i = start; i <= end; i++){
    count[vector[i] - min]++;
  }

  ll pos = 0;
  for(ll i = 0; i <= (max-min+1); i++){
    for(ll j = count[i]; count[i] > 0; j--){
      count[i]--;
      vector[pos] = i+min;
      pos++; 
    }
  }
}

// BucketSort implementation executing an insertion sort in each bucket (with n buckets -> size of the end - start) and setting max and min of the vector before running the algorithm
template <typename T>
void bucketSort(T* vector, ll start, ll end) {
  // Find max and minimum
  T max = vector[start];
  T min = vector[start];
  for(ll i = start + 1; i <= end; i++){
    if(max < vector[i]) max = vector[i];
    else {
      if (min > vector[i]) min = vector[i];
    }
  }

  int countSizeOfBuckets[end-start+1];
  int countSizeOfBucketsCopy[end-start+1];
  memset(countSizeOfBuckets, 0, (end-start+1) * sizeof(int));
  memset(countSizeOfBucketsCopy, 0, (end-start+1) * sizeof(int));

  ll bucketllerval = (max-min) / (end-start+1) + 1;

  for(ll i = start; i <= end; i++){
    ll bucketNum = (vector[i]-min) / (bucketllerval);
    countSizeOfBuckets[bucketNum]++;
    countSizeOfBucketsCopy[bucketNum]++;
  }

  T* buckets[end-start+1];
  for(ll i = 0; i < end-start+1; i++){
    buckets[i] = new T[countSizeOfBuckets[i]];
  }

  for(ll i = start; i <= end; i++){
    ll bucketNum = (vector[i]-min) / (bucketllerval);
    if(countSizeOfBuckets[bucketNum] > 0){
      buckets[bucketNum][countSizeOfBuckets[bucketNum]-1] = vector[i];
      countSizeOfBuckets[bucketNum]--;
    }
  }

  ll pos = 0;
  for(ll i = 0; i < end-start+1; i++){
    insertionSort(buckets[i], 0, countSizeOfBucketsCopy[i] - 1);
    for(ll j = 0; j < countSizeOfBucketsCopy[i]; j++){
      vector[pos] = buckets[i][j];
      pos++;
    }
  }
}

// Numbers converted to twos complement - the first bit (signal, it's 0 for negatives, and 1 for positives)
template <typename T>
bool getBit(T number, ll bitPosition)
{
  if (bitPosition == 8 * (ll)sizeof(T)){
    return (number < 0) ? 0 : 1;
  }
  return ((number & (static_cast<T>(1) << bitPosition)) != 0);
}

template <typename T>
void sortByBit(T* vector, ll &left, ll &right, ll bitPosition)
{
  while(left <= right)
  {
    while(left <= right && getBit(vector[left], bitPosition) == 0) left++;
    while(left <= right && getBit(vector[right], bitPosition) == 1) right--;
    if(left <= right){
      swap(&vector[left], &vector[right]);
      left++;
      right--;
    }
  }
}

template <typename T>
void radixSortBinary(T* vector, ll start, ll end, ll bit) {
  if (bit < 0 || start >= end) return;
  ll left = start;
  ll right = end;

  sortByBit(vector, left, right, bit);
  radixSortBinary(vector, start, right, bit - 1);
  radixSortBinary(vector, left, end, bit - 1);
}

// Classical binary radixSort implementation
template <typename T>
void radixSort(T* vector, ll start, ll end) {
  ll bit = 8 * (ll)sizeof(T);
  radixSortBinary(vector, start, end, bit);
}

#endif
