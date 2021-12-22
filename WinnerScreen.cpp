/*
 * This class displays a screen that shows who won the game
 * This class also displays a piece of text that shows who won the round
 */

#include "WinnerScreen.h"

using namespace std;

/*
 * Constructor for the WinnerScreen class
 * @param window -- the window of the game
 * @param playerNumber -- the player
 * @param s -- used to determine whether it is a round win or a game win
 */
WinnerScreen::WinnerScreen(sf::RenderWindow *window, int playerNumber, string s) {

    //Set string related stuff (font, size etc.)
    this->font.loadFromFile("../src/typwrng.ttf");
    this->window = window;
    this->helpWin = true;

    this->heading.setFont(this->font);
    this->heading.setFillColor(sf::Color::White);
    this->heading.setCharacterSize(60);

    //Determine the type of win and depending on the player
    if(s == "game"){
        if(playerNumber == 1){
            this->heading.setString("Player 1 has won the game");
        } else if(playerNumber == 2){
            this->heading.setString("Player 2 has won the game");
        }
    } else {
        if(playerNumber == 1){
            this->heading.setString("Player 1 has won the round");
        } else if(playerNumber == 2){
            this->heading.setString("Player 2 has won the round");
        }
    }

    this->heading.setPosition((this->window->getSize().x / 2) - (this->heading.getLocalBounds().width / 2), (this->window->getSize().y / 2) - (this->heading.getLocalBounds().height / 2)); //Display the string

    // background box
    this->background.setSize(sf::Vector2f(this->heading.getLocalBounds().width + 100.0f, this->heading.getLocalBounds().height + 100.0f));
    this->background.setFillColor(sf::Color(0,0,0,15));
    this->background.setPosition(this->heading.getPosition().x - 50.0f, this->heading.getPosition().y - 50.0f); 

}

/*
 * Destructor for this class
 */
WinnerScreen::~WinnerScreen()
{

}

/*
 * This function returns the instance of the window
 * @return  this->window
 */
sf::RenderWindow * WinnerScreen::getWindow()
{
    return this->window;
}
/*
 * This function clears the window -- makes it blank
 */
void WinnerScreen::clear()
{
    this->window->clear(sf::Color::Black);
}

/*
 * This function checks to see if the window is still running
 * @return window->isOpen()
 */
bool WinnerScreen::isRunning()
{
    return this->window->isOpen();
}

/*
 * This function draws the heading to the window
 */
void WinnerScreen::draw()
{
    this->window->draw(this->background);
    this->window->draw(this->heading);
    this->window->display();
}