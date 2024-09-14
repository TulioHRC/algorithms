#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../UI/include/sort/sortAlgorithms.hpp"

template <typename T>
void reverseVector(T * vector, int size){
  int j = size - 1;

  for(int i = 0; i < j; i++){
    T aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
    j--;
  }
}

// Vector types -> [0] - random, [1] - sorted, [2] - reversed sorted
template <typename T>
void initVector(T * vector, int size, int vectorType, unsigned int seed = 0){
  std::random_device rd;
  std::default_random_engine generator(seed ? seed : rd());
  std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

  for (int i=0; i<size; i++){
    vector[i] = (T)(distribution(generator));
  }

  if(vectorType != 0){
    quickSort(vector, 0, size - 1);
  } 

  if(vectorType == 2){
    reverseVector(vector, size);
  }
}

template <typename T>
bool verifySort(T* vector, ll size){
    for(ll i = 1; i < size; i++){
        if(vector[i-1] > vector[i]) return false;
    }
    return true;
}

template <typename T>
T* getVectorClone(T* vector, ll size){
    T* newVector = new T[size];

    for(int i = 0; i < size; i++){
        newVector[i] = vector[i];
    }

    return newVector;
}

// Variáveis globais
int* emptyVector;
ll emptyVectorSize;

int* oneElementVector;
ll oneElementVectorSize;

int* alreadySortedVector;
ll alreadySortedVectorSize;

int* reversedSortedVector;
ll reversedSortedVectorSize;

int* duplicatedVector;
ll duplicatedVectorSize;

ll randomVectorSizes;
int seed;
char* charRandomVector;
short int* shortIntRandomVector;
int* intRandomVector;
ll* longLongRandomVector;

void setup() {
    emptyVector = new int[0];
    emptyVectorSize = 0;

    oneElementVector = new int[1]{1};
    oneElementVectorSize = 1;

    alreadySortedVector = new int[5]{1, 2, 3, 4, 5};
    alreadySortedVectorSize = 5;

    reversedSortedVector = new int[5]{5, 4, 3, 2, 1};
    reversedSortedVectorSize = 5;

    duplicatedVector = new int[5]{5, -1, 5, 2, 1};
    duplicatedVectorSize = 5;

    std::srand(static_cast<unsigned>(std::time(0))); 

    seed = std::rand();
    randomVectorSizes = 10000;
    charRandomVector = new char[randomVectorSizes];
    shortIntRandomVector = new short int[randomVectorSizes];
    intRandomVector = new int[randomVectorSizes];
    longLongRandomVector = new ll[randomVectorSizes];
    initVector(charRandomVector, randomVectorSizes, 0, seed);
    initVector(shortIntRandomVector, randomVectorSizes, 0, seed);
    initVector(intRandomVector, randomVectorSizes, 0, seed);
    initVector(longLongRandomVector, randomVectorSizes, 0, seed);
}

int* emptyVectorClone;
int* oneElementVectorClone;
int* alreadySortedVectorClone;
int* reversedSortedVectorClone;
int* duplicatedVectorClone;
char* charRandomVectorClone;
short int* shortIntRandomVectorClone;
int* intRandomVectorClone;
ll* longLongRandomVectorClone;

void cloneTestCases(){
    emptyVectorClone = getVectorClone(emptyVector, emptyVectorSize);
    oneElementVectorClone = getVectorClone(oneElementVectorClone, oneElementVectorSize);
    alreadySortedVectorClone = getVectorClone(alreadySortedVector, alreadySortedVectorSize);
    reversedSortedVectorClone = getVectorClone(reversedSortedVector, reversedSortedVectorSize);
    duplicatedVectorClone = getVectorClone(duplicatedVector, duplicatedVectorSize);
    charRandomVectorClone = getVectorClone(charRandomVector, randomVectorSizes);
    shortIntRandomVectorClone = getVectorClone(shortIntRandomVector, randomVectorSizes);
    intRandomVectorClone = getVectorClone(intRandomVector, randomVectorSizes);
    longLongRandomVectorClone = getVectorClone(longLongRandomVector, randomVectorSizes);
}

template <typename T>
void testSort(void (*sortFunc)(T*, ll, ll), T* vectorClone, ll vectorSize, const std::string& testName) {
    SECTION(testName) {
        sortFunc(vectorClone, 0, vectorSize);
        REQUIRE(verifySort(vectorClone, vectorSize));
    }
}

TEST_CASE("BubbleSort test case", "[bubbleSort]") {
    cloneTestCases();

    testSort(bubbleSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(bubbleSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(bubbleSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(bubbleSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(bubbleSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(bubbleSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(bubbleSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(bubbleSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(bubbleSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("InsertionSort test case", "[insertionSort]") {
    cloneTestCases();

    testSort(insertionSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(insertionSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(insertionSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(insertionSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(insertionSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(insertionSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(insertionSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(insertionSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(insertionSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("SelectionSort test case", "[selectionSort]") {
    cloneTestCases();

    testSort(selectionSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(selectionSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(selectionSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(selectionSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(selectionSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(selectionSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(selectionSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(selectionSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(selectionSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("QuickSort test case", "[quickSort]") {
    cloneTestCases();

    testSort(quickSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(quickSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(quickSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(quickSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(quickSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(quickSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(quickSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(quickSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(quickSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("QuickSortMedian3 test case", "[quickSortMedian3]") {
    cloneTestCases();

    testSort(quickSortMedian3, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(quickSortMedian3, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(quickSortMedian3, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(quickSortMedian3, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(quickSortMedian3, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(quickSortMedian3, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(quickSortMedian3, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(quickSortMedian3, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(quickSortMedian3, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("QuickSortMedian3With test case", "[quickSortMedian3WithInsertionSort]") {
    cloneTestCases();

    testSort(quickSortMedian3WithInsertionSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(quickSortMedian3WithInsertionSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(quickSortMedian3WithInsertionSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(quickSortMedian3WithInsertionSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(quickSortMedian3WithInsertionSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(quickSortMedian3WithInsertionSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(quickSortMedian3WithInsertionSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(quickSortMedian3WithInsertionSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(quickSortMedian3WithInsertionSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("MergeSort test case", "[mergeSort]") {
    cloneTestCases();

    testSort(mergeSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(mergeSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(mergeSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(mergeSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(mergeSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(mergeSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(mergeSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(mergeSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(mergeSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("ShellSort test case", "[shellSort]") {
    cloneTestCases();

    testSort(shellSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(shellSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(shellSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(shellSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(shellSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(shellSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(shellSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(shellSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(shellSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("CountingSort test case", "[countingSort]") {
    cloneTestCases();

    testSort(countingSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(countingSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(countingSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(countingSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(countingSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(countingSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(countingSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(countingSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(countingSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("BucketSort test case", "[bucketSort]") {
    cloneTestCases();

    testSort(bucketSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(bucketSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(bucketSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(bucketSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(bucketSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(bucketSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(bucketSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(bucketSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(bucketSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("RadixSort test case", "[radixSort]") {
    cloneTestCases();

    testSort(radixSort, emptyVectorClone, emptyVectorSize, "Empty Vector");
    testSort(radixSort, oneElementVectorClone, oneElementVectorSize, "One Element Vector");
    testSort(radixSort, alreadySortedVectorClone, alreadySortedVectorSize, "Already Sorted Vector");
    testSort(radixSort, reversedSortedVectorClone, reversedSortedVectorSize, "Reversed Sorted Vector");
    testSort(radixSort, duplicatedVectorClone, duplicatedVectorSize, "Duplicated Elements Vector");
    testSort(radixSort, charRandomVectorClone, randomVectorSizes, "Char Random Vector");
    testSort(radixSort, shortIntRandomVectorClone, randomVectorSizes, "Short Int Random Vector");
    testSort(radixSort, intRandomVectorClone, randomVectorSizes, "Int Random Vector");
    testSort(radixSort, longLongRandomVectorClone, randomVectorSizes, "Long Long Random Vector");
}

TEST_CASE("Cleanup", "[cleanup]") {
    delete[] emptyVector;
    delete[] oneElementVector;
    delete[] alreadySortedVector;
    delete[] reversedSortedVector;
    delete[] duplicatedVector;
    delete[] charRandomVector;
    delete[] shortIntRandomVector;
    delete[] intRandomVector;
    delete[] longLongRandomVector;

    delete[] emptyVectorClone;
    delete[] oneElementVectorClone;
    delete[] alreadySortedVectorClone;
    delete[] reversedSortedVectorClone;
    delete[] duplicatedVectorClone;
    delete[] charRandomVectorClone;
    delete[] shortIntRandomVectorClone;
    delete[] intRandomVectorClone;
    delete[] longLongRandomVectorClone;
}
