#include "CharMenu.h"

/**
 * @brief: Class for a characters selection menu
 * @param window: window to be displayed when the char menu opens
 * @param playerNum: the player number who is currently making a character selection
 */
CharMenu::CharMenu(sf::RenderWindow *window, int playerNum)
{
    this->font.loadFromFile("../src/typwrng.ttf");  // Load in the font from the source directory
    this->window = window;                          // instantiate CharMenu attribute to the passed parameter
    this->charOpen = true;                          // instantiate charOpen to true. This variable tells the Menu class to keep this window open
    this->selectedChar = 0;                         // Variable to hold the selection of the user
    this->charCount = 2;                            // Number of characters
    
    // If the player who is selecting a character is player 1, execute this
    if (playerNum == 1)
    {

        // Display the text on the menu that says for player 1 to make their selection

        this->heading.setFont(this->font);
        this->heading.setString("Player 1 Select Character (press Return to Select)");
        this->heading.setCharacterSize(40);
        this->heading.setPosition(50.0f, 10.f);

        // character textures

        sf::Texture char1;
        char1.loadFromFile("../src/sprites/Player1/Player1WizIdle.png");
        this->charPreviews[0] = char1;

        // Load in the images of the characters for the user to select from

        sf::Texture char2;
        char2.loadFromFile("../src/sprites/Player1/Idle.png");
        this->charPreviews[1] = char2;

        // character boxes

        sf::RectangleShape char1Box;
        char1Box.setSize(sf::Vector2f(400.0f,300.0f));
        char1Box.setPosition(sf::Vector2f(this->window->getSize().x/ (2 + 1) * 1 - char1Box.getSize().x/2, this->window->getSize().y / 2));
        char1Box.setTexture(&charPreviews.find(0)->second);
        char1Box.setOutlineColor(sf::Color::Red);
        char1Box.setOutlineThickness(2.0f);
        this->charBoxes[0] = char1Box;

        sf::RectangleShape char2Box;
        char2Box.setSize(sf::Vector2f(400.0f,300.0f));

        // Set the boxes which contain the possible characters for the user to select

        char2Box.setPosition(sf::Vector2f(this->window->getSize().x/ (2 + 1) * 2 - char2Box.getSize().x/2, this->window->getSize().y / 2));
        char2Box.setTexture(&charPreviews.find(1)->second);
        char2Box.setOutlineColor(sf::Color::White);
        char2Box.setOutlineThickness(2.0f);
        this->charBoxes[1] = char2Box;
    }

    // If the player who is selecting is player 2

    else if(playerNum == 2)
    {

        // Load in the text of the 
        this->heading.setFont(this->font);
        this->heading.setString("Player 2 Select Character (press Return to Select)");
        this->heading.setCharacterSize(40);
        this->heading.setPosition(50.0f, 10.f);

        // character textures
        sf::Texture char1;
        char1.loadFromFile("../src/sprites/Player2/Player2WizIdle.png");
        this->charPreviews[0] = char1;

        sf::Texture char2;
        char2.loadFromFile("../src/sprites/Player2/Idle.png");
        this->charPreviews[1] = char2;

        // character boxes
        sf::RectangleShape char1Box;
        char1Box.setSize(sf::Vector2f(400.0f,300.0f));
        char1Box.setPosition(sf::Vector2f(this->window->getSize().x/ (2 + 1) * 1 - char1Box.getSize().x/2, this->window->getSize().y / 2));
        char1Box.setTexture(&charPreviews.find(0)->second);
        char1Box.setOutlineColor(sf::Color::Red);
        char1Box.setOutlineThickness(2.0f);
        this->charBoxes[0] = char1Box;

        sf::RectangleShape char2Box;
        char2Box.setSize(sf::Vector2f(400.0f,300.0f));

        // Set the boxes which hold the images of the characters to select from

        char2Box.setPosition(sf::Vector2f(this->window->getSize().x/ (2 + 1) * 2 - char2Box.getSize().x/2, this->window->getSize().y / 2));
        char2Box.setTexture(&charPreviews.find(1)->second);
        char2Box.setOutlineColor(sf::Color::White);
        char2Box.setOutlineThickness(2.0f);
        this->charBoxes[1] = char2Box;




    }
}

/**
 * @brief: Destructor method for the CharMenu class
 */
CharMenu::~CharMenu(){

}

/**
 * @brief: Method to display the Character selection menu to the user from the Menu class
 */
void CharMenu::draw() {
    this->window->draw(heading);
    for (size_t i = 0; i < this->charBoxes.size(); i++)
    {
        this->window->draw(charBoxes.find(i)->second);
    }
    this->window->display();
}

/**
 * @brief: Method which returns the window object of the character menu
 */
sf::RenderWindow* CharMenu::getWindow(){
    return this->window;
}

/**
 * @brief: Method to update the character menu window
 */
void CharMenu::update()
{
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // If the user entered return, close the window and make the selection

            if (event.key.code == sf::Keyboard::Return)
            {
                this->charOpen= false;
            }

            // If the user has entered left, then move the selection over 1

            if (event.key.code == sf::Keyboard::Left)
            {
                if (this->selectedChar - 1 >= 0)
                {
                    this->charBoxes.find(this->selectedChar)->second.setOutlineColor(sf::Color::White);
                    this->selectedChar--;
                    this->charBoxes.find(this->selectedChar)->second.setOutlineColor(sf::Color::Red);
                }
            }

            // If the user has entered right, then move the selection over 1

            if (event.key.code == sf::Keyboard::Right)
            {
                if (this->selectedChar + 1 < this->charCount)
                {
                    this->charBoxes.find(this->selectedChar)->second.setOutlineColor(sf::Color::White);
                    this->selectedChar++;
                    this->charBoxes.find(this->selectedChar)->second.setOutlineColor(sf::Color::Red);
                }
            }
        }
    }
}

/**
 * @brief: Method to clear the window contents
 */
void CharMenu::clear(){
    this->window->clear();
}

/**
 * @brief: Method to return a boolean value to see if a method is running or not
 */
bool CharMenu::isRunning()
{
    return this->window->isOpen();
}