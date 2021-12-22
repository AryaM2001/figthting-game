#ifndef HelpScreen_H
#define HelpScreen_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>

#define TEXT_ITEMS 3



class HelpScreen
{
public:
    HelpScreen(sf::RenderWindow *window);
    ~HelpScreen();
    void clear();
    void draw();
    void update();
    bool isRunning();
    bool helpOpen;
    sf::RenderWindow* getWindow();

private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text heading;
    sf::Text text;
    std::string line;
    std::ifstream instructions;
    std::list<sf::Text> textList;
    sf::FloatRect boundings;
};

#endif