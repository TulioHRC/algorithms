#ifndef SORTALGOMENU_H
#define SORTALGOMENU_H

#include "commandsMap.hpp"
#include "menu.hpp"
#include "terminalFunctions.hpp"
#include "sort/sortAlgorithms.hpp"

extern commandStringToChar_t commandStringToCharSortAlgorithmsMenu[];

// Vector types -> [0] - random, [1] - sorted, [2] - reversed sorted
template <typename T>
void initVector(T * vector, int size, int vectorType, unsigned int seed = 0);

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