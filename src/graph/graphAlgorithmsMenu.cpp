#include <random>
#include <algorithm>
#include <limits>
#include "graph/graphAlgorithmsMenu.hpp"

commandStringToChar_t commandStringToCharGraphAlgorithmsMenu[] = {
  {"Dijkstra", 'd'},
  {"A*", 'a'},
  {"BFS", 'e'},
  {"DFS", 'p'},
  {"Go Back", 'b'}
};

void runGraphAlgorithm(char algorithmKey)
{
  std::string filename;
  std::cin >> filename;

  char wantTimeEvaluation;

  do{
    std::cout << "Do you want time evaluation? (S/N) ";
    std::cin >> wantTimeEvaluation;
  } while (wantTimeEvaluation != 'S' && wantTimeEvaluation != 's' && wantTimeEvaluation != 'N' && wantTimeEvaluation != 'n');

  bool hasTimeEvaluation = (wantTimeEvaluation == 'S' || wantTimeEvaluation == 's') ? true : false; 

  int dataStructuresType;

  do{
    std::cout << "As data structure, you want Adjacency matrix [0] or Adjacency list [1]? ";
    std::cin >> dataStructuresType;
  } while (dataStructuresType != 0 && dataStructuresType != 1);

  int priorityQueueType;

  do{
    std::cout << "As priority queue, you want Min-heap [0] or Fibonacci-heap [1]? ";
    std::cin >> priorityQueueType;
  } while (priorityQueueType != 0 && priorityQueueType != 1);

  if(dataStructuresType == 0)
    executeGraphAlgorithm<AdjMatrix>(algorithmKey, filename, priorityQueueType, hasTimeEvaluation);
  else
    executeGraphAlgorithm<AdjList>(algorithmKey, filename, priorityQueueType, hasTimeEvaluation);

}

void executeAdjMatrixGraphAlgorithm(char algorithmKey, std::string filename, int priorityQueueType, bool hasTimeEvaluation)
{

}

void executeGraphAlgorithm<AdjMatrix>(char algorithmKey, std::string filename, int priorityQueueType, bool hasTimeEvaluation)
{
  long double distance = 0;


  auto start = std::chrono::high_resolution_clock::now();

  switch(algorithmKey)
  {
    case 'd':
      bubbleSort(vector, 0, vectorSize-1);
      break;
    case 'a':
      insertionSort(vector, 0, vectorSize-1);
      break;
    case 'e':
      selectionSort(vector, 0, vectorSize-1);
      break;
    case 'p':
      mergeSort(vector, 0, vectorSize-1);
      break;
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  std::cout << distance << std::endl;

  if(hasTimeEvaluation == true) std::cout << "\nRun time: " << duration.count()/1e6 << "ms" << std::endl;

  waitMessage("Executed.\n\nPress enter to continue..."); 
}

void openGraphAlgorithmsMenu()
{
  std::vector<std::string> operationsList = {
    "Dijkstra",
    "A*",
    "BFS",
    "DFS",
    "Go Back"
  };

  GraphAlgorithmMenu algorithmMenu = GraphAlgorithmMenu(operationsList, (int)operationsList.size());
  bool keepAlive = true;

  while(keepAlive){
    std::string operationSelected = algorithmMenu.selectItemOnMenu();

    algorithmMenu.commandSwitchWithGraphAlgorithmsPerformances(operationSelected);

    clearTerminal();
    if(nameToKey(operationSelected, commandStringToCharGraphAlgorithmsMenu) == 'b') keepAlive = false;
  }
}