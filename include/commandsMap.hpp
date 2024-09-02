#ifndef COMMANDS_MAP
#define COMMANDS_MAP

#include <string>

typedef struct commandStringToChar {
  std::string name;
  char key;
} commandStringToChar_t;

std::string keyToName(char key, commandStringToChar_t * commandsMap);

char nameToKey(std::string name, commandStringToChar_t * commandsMap);

#endif