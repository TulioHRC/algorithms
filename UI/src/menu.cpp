#include "menu.hpp"
#include "terminalFunctions.hpp"
#include <iostream>

Menu::Menu(std::vector<std::string> options, int size) : options(options), optionsQuantity(size), positionSelected(0) {}

void Menu::showMenu()
{
    for (int i = 0; i < this->optionsQuantity; ++i)
    {
        if (i == this->positionSelected)
            std::cout << "-> " << options[i] << std::endl;
        else
            std::cout << "   " << options[i] << std::endl;
    }
}

std::string Menu::selectItemOnMenu()
{
    char key;

    while(key != 13) {
        clearTerminal();

        std::cout << "Press enter to select...\n" << std::endl;
    
        showMenu();
            
        system("stty raw");
        key = (int)getchar(); 
        system("stty cooked");

        switch (key)
        {
            case 65: // Up arrow
                this->positionSelected = (this->positionSelected == 0) ? 0 : this->positionSelected - 1;
                break;
            case 66: // Down arrow
                this->positionSelected = (this->positionSelected == this->optionsQuantity - 1) ? this->positionSelected : this->positionSelected + 1;
        }   
    }
    return this->options[this->positionSelected];
}

void Menu::commandSwitch(std::string command) {}