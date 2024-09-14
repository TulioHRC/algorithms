#include <time.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "sort/sortAlgorithmsMenu.hpp"
#include "graph/graphAlgorithmsMenu.hpp"

commandStringToChar_t commandStringToChar[] = {
    {"Sorting Algorithms Menu", 'a'},
    {"Graph Search Algorithms Menu", 'b'},
    {"Exit", 'e'}
};

class MainMenu : public Menu {
  public:
    MainMenu(std::vector<std::string> options, int size) : Menu(options, size) {};

    void commandSwitch(std::string command){
      switch(nameToKey(command, commandStringToChar))
      {
        case 'a':
          openSortingAlgorithmsMenu();
          break;
        case 'b':
          openGraphAlgorithmsMenu();
          break;
        case 'e':
          clearTerminal();
          loadProgramTerminal("See you later!\n");
          exit(1);
          break;
      }
    }
};

int main(){
  std::vector<std::string> operationsList = {"Sorting Algorithms Menu", "Graph Search Algorithms Menu", "Exit"};
  MainMenu mainMenu = MainMenu(operationsList, 3);

  while(true){
    std::string operationSelected = mainMenu.selectItemOnMenu();

    mainMenu.commandSwitch(operationSelected);

    clearTerminal();
  }

  return 0;
}