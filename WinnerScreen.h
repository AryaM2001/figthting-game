#ifndef WINNERSCREEN_H
#define WINNERSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <SFML/Window.hpp>
#include "Game.h"

class WinnerScreen {
public:
    //functions
    WinnerScreen(sf::RenderWindow *window, int playerNum, std::string s);
    ~WinnerScreen();
    void clear();
    void draw();
    void update();
    bool isRunning();
    bool helpWin;
    sf::RenderWindow *getWindow();

private:
    //vars
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text heading;
    sf::RectangleShape background;
};

#endif //WINNERSCREEN_H
