#include "terminalFunctions.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>


void clearTerminal()
{
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void loadProgramTerminal(std::string message)
{
    clearTerminal();
    std::cout << message;

    for (int loop = 0; loop < 3; loop++)
    {
        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        std::cout << "\b\b\b   \b\b\b" << std::flush; // Clear points
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    clearTerminal();
}

void waitMessage(std::string message){
  std::cout << message << std::endl;
  
  std::cin.ignore();
  std::cin.get();
}
