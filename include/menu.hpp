#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu
{
    protected:
        std::vector<std::string> options;
        int optionsQuantity;
        int positionSelected;

    public: 
        Menu(std::vector<std::string> options, int size);

        void showMenu();
        std::string selectItemOnMenu();
        void virtual commandSwitch(std::string command);
        
};


#endif