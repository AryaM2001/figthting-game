/**
 * @brief Main file of the program. Only creates menu object and renders it 
 */

/* libraries and files used in the program */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Menu.h"

int main()
{
    // create main window that game and helpscreen will render to
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1000), "Best Fighting Game EVER!");

    //launch into main menu
    Menu menu(&window, window.getSize().x, window.getSize().y);
    menu.draw();

    //render menu to window
    window.display();
    menu.update(); 


    return 0;
}