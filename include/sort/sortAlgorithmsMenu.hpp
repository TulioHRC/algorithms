#ifndef SORTALGOMENU_H
#define SORTALGOMENU_H

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <random>
#include <chrono>
#include "commandsMap.hpp"
#include "menu.hpp"
#include "terminalFunctions.hpp"
#include "sort/sortAlgorithms.hpp"

extern commandStringToChar_t commandStringToCharSortAlgorithmsMenu[];

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
void executeSortingAlgorithm(
    T * vector, 
    int vectorSize, 
    int itemSize, 
    int vectorType, 
    char algorithmKey, 
    bool hasTimeEvaluation,
    unsigned int seed = 0
);

void runAlgorithm(char algorithmKey, unsigned int seed = 0);

class AlgorithmMenu : public Menu {
  public:
    AlgorithmMenu(std::vector<std::string> options, int size) : Menu(options, size) {};

    void commandSwitchWithSortingAlgorithmsPerformances(std::string command){
        char key = nameToKey(command, commandStringToCharSortAlgorithmsMenu);
        if(key != 'b' && key != 0){
            clearTerminal();
            runAlgorithm(key);
        }
        clearTerminal();
    }
};

void openSortingAlgorithmsMenu();

#endif