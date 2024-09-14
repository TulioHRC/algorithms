#include "commandsMap.hpp"

std::string keyToName(char key, commandStringToChar_t * commandsMap){
  int i=0;
  while (commandsMap[i].key){
    if (commandsMap[i].key == key) return commandsMap[i].name;
    i++;
  }
  return 0;
}

char nameToKey(std::string name, commandStringToChar_t * commandsMap){
  int i=0;
  while (commandsMap[i].key){
    if (commandsMap[i].name.compare(name) == 0) return commandsMap[i].key;
    i++;
  }
  return 0;
}