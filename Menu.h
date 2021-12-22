#ifndef SRC_MENU_H
#define SRC_MENU_H

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "HelpScreen.h"
#include "MapScreen.h"
#include "CharMenu.h"
#include <unistd.h>


#define TEXT_ITEMS 3



class Menu
{

public:
    Menu(sf::RenderWindow *window, float width, float height);
    ~Menu();

    void draw();
    void MoveUp();
    void MoveDown();
    void update();
    int GetPressedItem() { return selectedOption; }
    void setPressedItem(int item);
    void playMusic();
    void setOptions();
    bool menuOpen;
    int selectedOption;
    float width;
    float height;

private:
    sf::Font font;
    sf::Music menuMusic;
    sf::Text menu_item[TEXT_ITEMS];
    sf::RenderWindow* window;

};


#endif 

