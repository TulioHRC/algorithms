#ifndef SORT_ALGORITHM
#define SORT_ALGORITHM

#include <time.h>
#include <vector>
#include <iostream>

typedef long long ll;

// Utilitaries methods

template <typename T>
void swap(T *xp, T *yp);

template <typename T>
T median3(T a, T b, T c);

template <typename T>
void partition(T * vector, ll start, ll end, ll *i, ll *j);

template <typename T>
void partition3(T * vector, ll start, ll end, ll *i, ll *j);

template <typename T>
void merge(T * vector, ll start, ll mid, ll end);

template <typename T>
bool getBit(T number, ll bitPosition);

template <typename T>
void sortByBit(T* vector, ll &left, ll &right, ll bitPosition);

template <typename T>
void verifyVectorIsOrdened(T* vector);

// Sort Algorithms

// Classical bubble sort implementation
template <typename T>
void bubbleSort(T* vector, ll start, ll end);

// Classical insertion sort implementation
template <typename T>
void insertionSort(T* vector, ll start, ll end);

// Classical selection sort implementation
template <typename T>
void selectionSort(T* vector, ll start, ll end);

// Classical quick sort implementation
template <typename T>
void quickSort(T* vector, ll start, ll end);

template <typename T>
void quickSortMedian3(T* vector, ll start, ll end);

template <typename T>
void quickSortMedian3WithInsertionSort(T* vector, ll start, ll end);

template <typename T>
void mergeSort(T* vector, ll start, ll end);

template <typename T>
void shellSort(T* vector, ll start, ll end);

template <typename T>
void countingSort(T* vector, ll start, ll end);

template <typename T>
void bucketSort(T* vector, ll start, ll end);

template <typename T>
void radixSort(T* vector, ll start, ll end, ll actualBit);

#endif
