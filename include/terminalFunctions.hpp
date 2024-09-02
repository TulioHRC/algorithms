#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>


void clearTerminal();
void loadProgramTerminal(std::string);
int selectListItemTerminal(std::vector<std::string>, bool showAllOptions); // Returns the index of the selected item
void waitMessage(std::string message);

#endif