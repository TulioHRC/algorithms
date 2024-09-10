#include "graph/graphAlgorithmsMenu.hpp"

commandStringToChar_t commandStringToCharGraphAlgorithmsMenu[] = {
  {"Go Back", 'b'}
};

void runGraphAlgorithm(char algorithmKey, unsigned int seed)
{

}

void openGraphAlgorithmsMenu()
{
  std::vector<std::string> operationsList = {
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