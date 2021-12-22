
#include "MapScreen.h"

/**
 * @brief: Class for a map selection menu
 * @param window: window to be displayed when the map menu opens
 */
MapScreen::MapScreen(sf::RenderWindow *window)
{
    this->font.loadFromFile("../src/typwrng.ttf");  // Load in the font from the source directory
    this->window = window;                          // instantiate MapMenu attribute to the passed parameter
    this->mapOpen = true;                           // instantiate MapOpen to true. This variable tells the Menu class to keep this window open
    this->selectedMap = 0;                          // Variable to hold the selection of the user
    this->mapCount = 2;                             // Number of Maps

    this->window->setKeyRepeatEnabled(false);

    // Set the text to be displayed to the user while the selection map screen is up

    this->heading.setFont(this->font);
    this->heading.setString("Choose your map\n");
    this->heading.setCharacterSize(60);
    int centerWindow = this->window->getSize().x/2;
    float centerHeading = this->heading.getLocalBounds().width/2;
    this->heading.setPosition(centerWindow - centerHeading, 100.f);

    // map textures to the available maps for selection

    sf::Texture map1;
    map1.loadFromFile("../src/Background/background.jpeg");
    this->mapPreviews[0] = map1;

    sf::Texture map2;
    map2.loadFromFile("../src/Background/lava.jpg");
    this->mapPreviews[1] = map2;

    // map boxes that can be selected

    sf::RectangleShape map1Box;
    map1Box.setSize(sf::Vector2f(533.0f,300.0f));
    map1Box.setPosition(sf::Vector2f(this->window->getSize().x/ (2 + 1) * 1 - map1Box.getSize().x/2, this->window->getSize().y / 2));
    map1Box.setTexture(&mapPreviews.find(0)->second);
    map1Box.setOutlineColor(sf::Color::Red);
    map1Box.setOutlineThickness(2.0f);
    this->mapBoxes[0] = map1Box;

    sf::RectangleShape map2Box;
    map2Box.setSize(sf::Vector2f(533.0f,300.0f));

    // Set the position of the boxes

    map2Box.setPosition(sf::Vector2f(this->window->getSize().x/ (2 + 1) * 2 - map2Box.getSize().x/2, this->window->getSize().y / 2));
    map2Box.setTexture(&mapPreviews.find(1)->second);
    map2Box.setOutlineColor(sf::Color::White);
    map2Box.setOutlineThickness(2.0f);
    this->mapBoxes[1] = map2Box;
}

/**
 * @brief: Destructor method for the MapMenu class
 */
MapScreen::~MapScreen(){

}

/**
 * @brief: Method to display the map selection menu to the user from the Menu class
 */
void MapScreen::draw() {
    this->window->draw(heading);
    for (size_t i = 0; i < this->mapBoxes.size(); i++)
    {
        this->window->draw(mapBoxes.find(i)->second);
    }
    this->window->display();
}

/**
 * @brief: Method which returns the window object of the character menu
 */
sf::RenderWindow* MapScreen::getWindow(){
    return this->window;
}

/**
 * @brief: Method to update the character menu window
 */
void MapScreen::update()
{
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::KeyReleased)
        {
            // If the user entered return, close the window and make the selection
            if (event.key.code == sf::Keyboard::Return)
            {
                this->mapOpen= false;
            }

            // If the user has entered left, then move the selection over 1

            if (event.key.code == sf::Keyboard::Left)
            {
                if (this->selectedMap - 1 >= 0)
                {
                    this->mapBoxes.find(this->selectedMap)->second.setOutlineColor(sf::Color::White);
                    this->selectedMap--;
                    this->mapBoxes.find(this->selectedMap)->second.setOutlineColor(sf::Color::Red);
                }
            }

            // If the user has entered right, then move the selection over 1

            if (event.key.code == sf::Keyboard::Right)
            {
                if (this->selectedMap + 1 < this->mapCount)
                {
                    this->mapBoxes.find(this->selectedMap)->second.setOutlineColor(sf::Color::White);
                    this->selectedMap++;
                    this->mapBoxes.find(this->selectedMap)->second.setOutlineColor(sf::Color::Red);
                }
            }
        }
    }
}

/**
 * @brief: Method to clear the window contents
 */
void MapScreen::clear(){
    this->window->clear();
}

/**
 * @brief: Method to return a boolean value to see if a method is running or not
 */
bool MapScreen::isRunning()
{
    return this->window->isOpen();
}
