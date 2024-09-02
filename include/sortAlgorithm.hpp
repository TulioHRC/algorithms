#ifndef SORT_ALGORITHM
#define SORT_ALGORITHM

#include <time.h>
#include <vector>
#include <iostream>


typedef long long ll;

typedef struct settings {
  ll vectorSize;
  ll itemSize;
  const char * vectorType;
  unsigned int seed;
} settings_t;

typedef struct sortPerformance {
  ll comparations;
  ll movements;
  ll functionCalls;
  const char * sortName;
  __time_t milissecs;
  settings_t settings;
} sortPerformance_t;

template <typename T>
class SortAlgorithms {
private:
  sortPerformance_t sortPerformanceObject;
  void incrementComparations(ll numToIncrement);
  void incrementMovements(ll numToIncrement);
  void incrementFunctionCalls(ll numToIncrement);
  void swap(T *xp, T *yp);
  T median3(T a, T b, T c);
  void partition(T * vector, ll start, ll end, ll *i, ll *j);
  void partition3(T * vector, ll start, ll end, ll *i, ll *j);
  void merge(T * vector, ll start, ll mid, ll end);
  bool getBit(T number, ll bitPosition);
  void sortByBit(T* vector, ll &left, ll &right, ll bitPosition);
  void verifyVectorIsOrdened(T* vector);

public:
  SortAlgorithms(ll vectorSize, ll itemSize, const char * vectorType, unsigned int seed);

  void printPerformance();
  void resetPerformance(ll vectorSize, ll itemSize);
  sortPerformance_t getSortPerformanceObject();

  void runAlgorithm(T* vector, char whichAlgorithm);

  void runBubbleSort(T* vector, ll start, ll end);
  void runInsertionSort(T* vector, ll start, ll end);
  void runSelectionSort(T* vector, ll start, ll end);
  void runQuickSort(T* vector, ll start, ll end);
  void runQuickSortMedian3(T* vector, ll start, ll end);
  void runQuickSortMedian3WithInsertionSort(T* vector, ll start, ll end);
  void runMergeSort(T* vector, ll start, ll end);
  void runShellSort(T* vector, ll start, ll end);
  void runCountingSort(T* vector, ll start, ll end);
  void runBucketSort(T* vector, ll start, ll end);
  void runRadixSort(T* vector, ll start, ll end, ll actualBit);

};

template <typename T>
SortAlgorithms<T>::SortAlgorithms(ll vectorSize, ll itemSize, const char * vectorType, unsigned int seed) {
    sortPerformanceObject.settings.vectorSize = vectorSize;
    sortPerformanceObject.settings.itemSize = itemSize;
    sortPerformanceObject.settings.vectorType = vectorType;
    sortPerformanceObject.settings.seed = seed;
    sortPerformanceObject.sortName = "";
    sortPerformanceObject.comparations = 0;
    sortPerformanceObject.movements = 0;
    sortPerformanceObject.functionCalls = 0;
}

template <typename T>
void SortAlgorithms<T>::incrementComparations(ll numToIncrement) {
    sortPerformanceObject.comparations += numToIncrement;
}

template <typename T>
void SortAlgorithms<T>::incrementMovements(ll numToIncrement) {
    sortPerformanceObject.movements += numToIncrement;
}

template <typename T>
void SortAlgorithms<T>::incrementFunctionCalls(ll numToIncrement) {
    sortPerformanceObject.functionCalls += numToIncrement;
}

template <typename T>
void SortAlgorithms<T>::swap(T *xp, T *yp){
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
    incrementMovements(3);
}

template <typename T>
T SortAlgorithms<T>::median3 (T a, T b, T c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

template <typename T>
void SortAlgorithms<T>::partition(T * vector, ll start, ll end, ll *i, ll *j) {
  T pivotValue = vector[(start + end)/2];
  incrementFunctionCalls(1);
  *i = start;
  *j = end;

  do {
    incrementComparations(2);
    while(pivotValue > vector[*i]) {(*i)++; incrementComparations(1);};
    while(pivotValue < vector[*j]) {(*j)--; incrementComparations(1);};

    if(*i <= *j){
      swap(&vector[*i], &vector[*j]);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

template <typename T>
void SortAlgorithms<T>::partition3(T * vector, ll start, ll end, ll *i, ll *j) {
  T pivotValue = median3(vector[start], vector[(start + end)/2], vector[end]);

  incrementFunctionCalls(1);
  *i = start;
  *j = end;

  do {
    incrementComparations(2);
    while(pivotValue > vector[*i]) {(*i)++; incrementComparations(1);};
    while(pivotValue < vector[*j]) {(*j)--; incrementComparations(1);};

    if(*i <= *j){
      swap(&vector[*i], &vector[*j]);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

template <typename T>
void SortAlgorithms<T>::merge(T * vector, ll start, ll mid, ll end){
  T * result = new T[end - start + 1];
  ll i = 0;
  ll j = 0;
  ll k = 0;
  while (i < (mid - start + 1) && j < (end - mid)) {
    incrementComparations(1);
    if (vector[start + i] < vector[j + mid + 1]) {
      incrementMovements(1);
      result[k] = vector[start + i];
      i++;
    } else {
      incrementMovements(1);
      result[k] = vector[j + mid + 1];
      j++;
    }
    k++;
  }

  if (k < (end - start + 1)) {
    for(; i < (mid - start + 1); i++) {
      incrementMovements(1);
      result[k] = vector[start + i];
      k++;
    }
    for(; j < (end - mid); j++) {
      incrementMovements(1);
      result[k] = vector[mid + 1 + j];
      k++;
    }
  }

  for(ll i = start; i <= end; i++){
    incrementMovements(1);
    vector[i] = result[i-start];
  }
}


template <typename T>
void SortAlgorithms<T>::runAlgorithm(T* vector, char whichAlgorithm) {
  switch(whichAlgorithm)
  {
    case 'a':
      runBubbleSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'i':
      runInsertionSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 's':
      runSelectionSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'm':
      runMergeSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'q':
      runQuickSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'j':
      runQuickSortMedian3(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'o':
      runQuickSortMedian3WithInsertionSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'h':
      runShellSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'c':
      runCountingSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'u':
      runBucketSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1);
      break;
    case 'r':
      runRadixSort(vector, 0, this->sortPerformanceObject.settings.vectorSize-1, 8 * (ll)sizeof(T));
      break;
  }

  verifyVectorIsOrdened(vector);

}

template <typename T>
void SortAlgorithms<T>::runBubbleSort(T* vector, ll start, ll end) {
  for(ll i = start; i < end; i++){
    for(ll j = 1; j <= end - i; j++){
      incrementComparations(1);
      if(vector[j] < vector[j-1]) swap(&vector[j-1], &vector[j]);
    }
  }
}

template <typename T>
void SortAlgorithms<T>::runInsertionSort(T* vector, ll start, ll end) {
  ll behindPos, aux;
  incrementFunctionCalls(1);

  for (ll pos = start; pos < end; pos++){
    incrementMovements(1);
    aux = vector[pos + 1];
    behindPos = pos;
    incrementComparations(1);
    while((behindPos >= start) && (aux < vector[behindPos])){
      incrementMovements(1);
      vector[behindPos + 1] = vector[behindPos];
      behindPos--;
      incrementComparations(1);
    }

    incrementMovements(1);
    vector[behindPos + 1] = aux;
  }
}

template <typename T>
void SortAlgorithms<T>::runSelectionSort(T* vector, ll start, ll end) {
  ll actualMinPos;
  incrementFunctionCalls(1);

  for (ll pos = start; pos < end; pos++){
    actualMinPos = pos;
    for (ll i = pos + 1; i <= end; i ++){
      incrementComparations(1);
      if (vector[i] < vector[actualMinPos]){
        actualMinPos = i;
      }
    }
    if(actualMinPos != pos) swap(&vector[pos], &vector[actualMinPos]);
  }
}

template <typename T>
void SortAlgorithms<T>::runQuickSort(T* vector, ll start, ll end) {
  ll i, j;
  incrementFunctionCalls(1);
  partition(vector, start, end, &i, &j);

  if(start < j) runQuickSort(vector, start, j); 
  if(i < end) runQuickSort(vector, i, end); 
}

template <typename T>
void SortAlgorithms<T>::runQuickSortMedian3(T* vector, ll start, ll end) {
  ll i, j;
  incrementFunctionCalls(1);
  partition3(vector, start, end, &i, &j);

  if(start < j) runQuickSortMedian3(vector, start, j); 
  if(i < end) runQuickSortMedian3(vector, i, end); 
}

template <typename T>
void SortAlgorithms<T>::runQuickSortMedian3WithInsertionSort(T* vector, ll start, ll end) {
  ll i, j;
  incrementFunctionCalls(1);
  
  partition3(vector, start, end, &i, &j);

  if(start < j){
    if(j - start > 50) runQuickSortMedian3WithInsertionSort(vector, start, j);
    else runInsertionSort(vector, start, j);
  }
  if(i < end){
    if(end - i > 50) runQuickSortMedian3WithInsertionSort(vector, i, end);
    else runInsertionSort(vector, i, end);
  }
}

template <typename T>
void SortAlgorithms<T>::runMergeSort(T* vector, ll start, ll end) {
  if(start < end){
    ll mid = (start + end)/2;
    incrementFunctionCalls(2);
    runMergeSort(vector, start, mid);
    runMergeSort(vector, mid + 1, end);
    merge(vector, start, mid, end);
  }
}

template <typename T>
void SortAlgorithms<T>::runShellSort(T* vector, ll start, ll end) {
  incrementFunctionCalls(1);

  for(ll h = (end-start+1)/2; h > 0; h /= 2){
    for(ll i = h; i < (end-start+1); i++){
      incrementMovements(1);
      T aux = vector[i];
      ll j;
      incrementComparations(1);
      for(j = i; j >= h && vector[j-h] > aux; j-=h){
        incrementComparations(1);
        incrementMovements(1);
        vector[j] = vector[j-h];
      }
      incrementMovements(1);
      vector[j] = aux;
    }
  }
}

template <typename T>
void SortAlgorithms<T>::runCountingSort(T* vector, ll start, ll end) {
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
      incrementMovements(1);
      vector[pos] = i+min;
      pos++; 
    }
  }
}

template <typename T>
void SortAlgorithms<T>::runBucketSort(T* vector, ll start, ll end) {
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
    runInsertionSort(buckets[i], 0, countSizeOfBucketsCopy[i] - 1);
    for(ll j = 0; j < countSizeOfBucketsCopy[i]; j++){
      incrementMovements(1);
      vector[pos] = buckets[i][j];
      pos++;
    }
  }
}

// Numbers converted to twos complement - the first bit (signal, is 0 for negatives, and 1 for positives)
template <typename T>
bool SortAlgorithms<T>::getBit(T number, ll bitPosition)
{
  if (bitPosition == 8 * (ll)sizeof(T)){
    return (number < 0) ? 0 : 1;
  }
  return ((number & (static_cast<T>(1) << bitPosition)) != 0);
}

template <typename T>
void SortAlgorithms<T>::sortByBit(T* vector, ll &left, ll &right, ll bitPosition)
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
void SortAlgorithms<T>::runRadixSort(T* vector, ll start, ll end, ll bit) {
  if (bit < 0 || start >= end) return;
  ll left = start;
  ll right = end;

  sortByBit(vector, left, right, bit);
  incrementFunctionCalls(2);
  runRadixSort(vector, start, right, bit - 1);
  runRadixSort(vector, left, end, bit - 1);
}

template <typename T>
void SortAlgorithms<T>::verifyVectorIsOrdened(T* vector)
{
  for(ll i = 1; i < this->sortPerformanceObject.settings.vectorSize; i++){
    if(vector[i-1] > vector[i]){
      exit(1);
    }
  }
}

template <typename T>
void SortAlgorithms<T>::printPerformance()
{
  std::cout << "Vector Size: " << this->sortPerformanceObject.settings.vectorSize << " elements"
    << "\nItem Size: " << this->sortPerformanceObject.settings.itemSize << " bits"
    << "\nTime: " << this->sortPerformanceObject.milissecs << "ms" 
    << "\nComparations: " << this->sortPerformanceObject.comparations
    << "\nMovements: " << this->sortPerformanceObject.movements
    << "\nFunction Calls: " << this->sortPerformanceObject.functionCalls 
  << std::endl;
}

template <typename T>
void SortAlgorithms<T>::resetPerformance(ll vectorSize, ll itemSize)
{
  sortPerformanceObject.settings.vectorSize = vectorSize;
  sortPerformanceObject.settings.itemSize = itemSize;
  sortPerformanceObject.comparations = 0;
  sortPerformanceObject.movements = 0;
  sortPerformanceObject.functionCalls = 0;
}

template <typename T>
sortPerformance_t SortAlgorithms<T>::getSortPerformanceObject() 
{
  return sortPerformanceObject;
}

#endif
