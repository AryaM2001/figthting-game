#ifndef CharMenu_H
#define CharMenu_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>

#define TEXT_ITEMS 3



class CharMenu
{
public:
    CharMenu(sf::RenderWindow *window, int playerNum);
    ~CharMenu();
    void clear();
    void draw();
    void update();
    bool isRunning();
    bool charOpen;
    sf::RenderWindow* getWindow();
    int selectedChar;

private:
    sf::RenderWindow* window;
    std::string player;
    sf::Font font;
    sf::Text heading;
    sf::RectangleShape rectangle;
    sf::Texture preview;
    sf::Text text;
    std::string line;
    sf::FloatRect boundings;
    int charCount;
    std::map<int, sf::RectangleShape> charBoxes;
    std::map<int, sf::Texture> charPreviews;
};


#endif //SRC_MENU_H