#include <time.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <random>
#include <chrono>
#include "sort/sortAlgorithmsMenu.hpp"
#include "sort/sortAlgorithms.hpp"

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
    quickSort(vector, 0, size - 1);
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
    bool hasTimeEvaluation,
    unsigned int seed
  )
{
  auto start = std::chrono::high_resolution_clock::now();

  switch(algorithmKey)
  {
    case 'a':
      bubbleSort(vector, 0, vectorSize-1);
      break;
    case 'i':
      insertionSort(vector, 0, vectorSize-1);
      break;
    case 's':
      selectionSort(vector, 0, vectorSize-1);
      break;
    case 'm':
      mergeSort(vector, 0, vectorSize-1);
      break;
    case 'q':
      quickSort(vector, 0, vectorSize-1);
      break;
    case 'j':
      quickSortMedian3(vector, 0, vectorSize-1);
      break;
    case 'o':
      quickSortMedian3WithInsertionSort(vector, 0, vectorSize-1);
      break;
    case 'h':
      shellSort(vector, 0, vectorSize-1);
      break;
    case 'c':
      countingSort(vector, 0, vectorSize-1);
      break;
    case 'u':
      bucketSort(vector, 0, vectorSize-1);
      break;
    case 'r':
      radixSort(vector, 0, vectorSize-1, 8 * (ll)sizeof(T));
      break;
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  printVector(vector, vectorSize);

  if(hasTimeEvaluation == true) std::cout << "\nRun time: " << duration.count()/1e6 << "ms" << std::endl;

  waitMessage("Sorted.\n\nPress enter to continue..."); 
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
  
  char wantTimeEvaluation;

  do{
    std::cout << "Do you want time evaluation? (S/N) ";
    std::cin >> wantTimeEvaluation;
  } while (wantTimeEvaluation != 'S' && wantTimeEvaluation != 's' && wantTimeEvaluation != 'N' && wantTimeEvaluation != 'n');

  bool hasTimeEvaluation = (wantTimeEvaluation == 'S' || wantTimeEvaluation == 's') ? true : false; 

  if(itemSize == 8){
    char * vector = new char[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, hasTimeEvaluation, seed);

  } else if (itemSize == 16){
    short int * vector = new short int[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, hasTimeEvaluation, seed);
  
  } else if (itemSize == 32){
    int * vector = new int[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, hasTimeEvaluation, seed);
  
  } else { // 64 bits
    long long * vector = new long long[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, hasTimeEvaluation, seed);
  
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