#ifndef MapScreen_H
#define MapScreen_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>

#define TEXT_ITEMS 3



class MapScreen
{
public:
    MapScreen(sf::RenderWindow *window);
    ~MapScreen();
    void clear();
    void draw();
    void update();
    bool isRunning();
    bool mapOpen;
    sf::RenderWindow* getWindow();
    int selectedMap;

private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text heading;
    sf::RectangleShape rectangle;
    sf::Texture preview;
    sf::Text text;
    std::string line;
    sf::FloatRect boundings;
    int mapCount;
    std::map<int, sf::RectangleShape> mapBoxes;
    std::map<int, sf::Texture> mapPreviews;
};


#endif //SRC_MENU_H
