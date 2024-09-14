#ifndef GRAPHALGOMENU_H
#define GRAPHALGOMENU_H

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <random>
#include <chrono>
#include "commandsMap.hpp"
#include "menu.hpp"
#include "terminalFunctions.hpp"
#include "graph/graphAlgorithms.hpp"
#include "graph/adjList.hpp"
#include "graph/adjMatrix.hpp"

extern commandStringToChar_t commandStringToCharGraphAlgorithmsMenu[];

void runGraphAlgorithm(char algorithmKey);

template
void executeAdjMatrixGraphAlgorithm(char algorithmKey, std::string filename, int priorityQueueType, bool hasTimeEvaluation);
void executeAdjListGraphAlgorithm(char algorithmKey, std::string filename, int priorityQueueType, bool hasTimeEvaluation);


class GraphAlgorithmMenu : public Menu {
  public:
    GraphAlgorithmMenu(std::vector<std::string> options, int size) : Menu(options, size) {};

    void commandSwitchWithGraphAlgorithmsPerformances(std::string command){
        char key = nameToKey(command, commandStringToCharGraphAlgorithmsMenu);
        if(key != 'b' && key != 0){
            clearTerminal();
            runGraphAlgorithm(key);
        }
        clearTerminal();
    }
};

void openGraphAlgorithmsMenu();

#endif