#include <time.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <random>
#include <vector>
#include "sortAlgorithmsMenu.hpp"

commandStringToChar_t commandStringToCharSortAlgorithmsMenu[] = {
  {"Bubble Sort", 'a'},
  {"Insert Sort", 'i'},
  {"Selection Sort", 's'},
  {"Merge Sort", 'm'},
  {"Quick Sort", 'q'},
  {"Quick Sort Median 3", 'j'},
  {"Quick Sort Median 3 with Insert Sort", 'o'},
  {"Shell Sort", 'h'},
  {"Counting Sort", 'c'},
  {"Bucket Sort", 'u'},
  {"Radix Sort", 'r'},
  {"Go Back", 'b'}
};

const char * vectorTypeIdToNameList[] = {
  "Random",
  "Sorted",
  "Reversed Sorted"
};

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

template <typename T>
void initVector(T * vector, int size, int vectorType, unsigned int seed){
  std::random_device rd;
  std::default_random_engine generator(seed ? seed : rd());
  std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

  for (int i=0; i<size; i++){
    vector[i] = (T)(distribution(generator));
  }

  if(vectorType != 0){
    SortAlgorithms<T> * temporarySort = new SortAlgorithms<T>(size, sizeof(T), vectorTypeIdToNameList[0], 0);
    temporarySort->runQuickSort(vector, 0, size - 1);
    delete temporarySort;
  } 

  if(vectorType == 2){
    reverseVector(vector, size);
  }
}

template<typename T>
void printVector(T * vector, int size){
  std::cout << std::endl;
  for (int i=0; i<size; i++){
    std::cout << (long long)vector[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void executeSortingAlgorithm(
    T * vector, 
    int vectorSize, 
    int itemSize, 
    int vectorType, 
    char algorithmKey, 
    unsigned int seed
  )
{
  SortAlgorithms<T> sortAlgorithms(vectorSize, itemSize, vectorTypeIdToNameList[vectorType], seed);

  switch(algorithmKey)
  {
    case 'a':
      runBubbleSort(vector, 0, vectorSize-1);
      break;
    case 'i':
      runInsertionSort(vector, 0, vectorSize-1);
      break;
    case 's':
      runSelectionSort(vector, 0, vectorSize-1);
      break;
    case 'm':
      runMergeSort(vector, 0, vectorSize-1);
      break;
    case 'q':
      runQuickSort(vector, 0, vectorSize-1);
      break;
    case 'j':
      runQuickSortMedian3(vector, 0, vectorSize-1);
      break;
    case 'o':
      runQuickSortMedian3WithInsertionSort(vector, 0, vectorSize-1);
      break;
    case 'h':
      runShellSort(vector, 0, vectorSize-1);
      break;
    case 'c':
      runCountingSort(vector, 0, vectorSize-1);
      break;
    case 'u':
      runBucketSort(vector, 0, vectorSize-1);
      break;
    case 'r':
      runRadixSort(vector, 0, vectorSize-1, 8 * (ll)sizeof(T));
      break;
  }

  printVector(vector, vectorSize);
  waitMessage("Sorted."); 
}

void runAlgorithm(char algorithmKey, unsigned int seed)
{
  int vectorSize, itemSize, vectorType;
  std::cout << "Vector size: "; std::cin >> vectorSize;

  do{
    std::cout << "Item size (only 8, 16, 32 and 64) in bits: ";
    std::cin >> itemSize;
  } while (itemSize != 8 && itemSize != 16 && itemSize != 32 && itemSize != 64);

  do{
    std::cout << "Vector type [0] - random, [1] - sorted, [2] - reversed sorted: ";
    std::cin >> vectorType;
  } while (vectorType != 0 && vectorType != 1 && vectorType != 2);

  if(itemSize == 8){
    char * vector = new char[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, seed);

  } else if (itemSize == 16){
    short int * vector = new short int[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, seed);
  
  } else if (itemSize == 32){
    int * vector = new int[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, seed);
  
  } else { // 64 bits
    long long * vector = new long long[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, seed);
  
  }

}

void openSortingAlgorithmsMenu()
{
  std::vector<std::string> operationsList = {
    "Bubble Sort",
    "Insert Sort",
    "Selection Sort",
    "Merge Sort",
    "Quick Sort",
    "Quick Sort Median 3",
    "Quick Sort Median 3 with Insert Sort",
    "Shell Sort",
    "Counting Sort",
    "Bucket Sort",
    "Radix Sort",
    "Go Back"
  };

  AlgorithmMenu algorithmMenu = AlgorithmMenu(operationsList, (int)operationsList.size());
  bool keepAlive = true;

  while(keepAlive){
    std::string operationSelected = algorithmMenu.selectItemOnMenu();

    algorithmMenu.commandSwitchWithSortingAlgorithmsPerformances(operationSelected);

    clearTerminal();
    if(nameToKey(operationSelected, commandStringToCharSortAlgorithmsMenu) == 'b') keepAlive = false;
  }
}