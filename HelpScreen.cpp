/*
 * @brief This class displays a screen that shows the instructions for playing the game and it shows the text on the window
 */
#include "HelpScreen.h"

/*
 * @brief Constructor for the HelpScreen class
 * @param window the window of the game on which the changes need to be made and on thich the help menu is displayed
 */

HelpScreen::HelpScreen(sf::RenderWindow *window)
{
    this->font.loadFromFile("../src/typwrng.ttf"); //loading the font
    this->window = window; //storing the parameter window to the local window
    this->helpOpen = true;

    this->heading.setFont(this->font);  //sets the font fo the variable type sf::Text
    this->heading.setString("How To Play\n");
    this->heading.setCharacterSize(60);
    this->heading.setPosition(this->window->getSize().x/2 - this->heading.getLocalBounds().width/2, 10.f); //sets position relative to screen size
    this->text.setFont(font); 

    //sets the text to new line and then pushes back a bunch of newline characters to add some space between heading and the text
    this->text.setString("\n");
    this->textList.push_back(text); 
    this->textList.push_back(text);
    this->textList.push_back(text);
    this->textList.push_back(text);
    

    this->text = sf::Text("", font, 30); 
    this->instructions.open("../src/Instructions.txt"); //opens the instructions file to read from 
    
    if(this->instructions.is_open()) //opens the file
    {
        //reads each sentence from the file and pushes the text in a list called textList
        while(std::getline(this->instructions, this->line))
        {
            this->text.setString(this->line);
            this->textList.push_back(this->text);
        }
    }
    this->instructions.close(); //closes the file
}

/*
 * @brief Destructor for this class
 */
HelpScreen::~HelpScreen()
{
}


/*
 *  @brief window draws the sf variables onto the window which are then displayed
 *
 */
void HelpScreen::draw() {
    this->window->draw(heading); //draws the heading

    float i = 0;
    //loop goes through the list of text and sets the position for each value in it which it then draws onto the window
    for(std::list<sf::Text>::iterator it = textList.begin(); it != textList.end(); ++it)
    {
        sf::Text& text = *it;
        sf::FloatRect boundings = text.getLocalBounds();
        text.setPosition(0.0f, i * (boundings.height + 5));
        ++i;

        if(i!=0)
            this->window->draw(text);
    }
    //displays all the drawn items onto the window
    this->window->display();
}

/*
 * @brief function returns the instance of the window
 * @return  this->window
 */
sf::RenderWindow* HelpScreen::getWindow(){
    return this->window;
}

/*
 * @brief updates helpOpen variable
 * @details function checks if the escape key is pressed or not and updates the boolean helpOpen to false
 */
void HelpScreen::update()
{
    //checks if the escape key is pressed
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {   
        this->helpOpen = false; //changes the value to false
    }
}


/*
 * @brief function clears the window -- makes it blank
 */
void HelpScreen::clear(){
    this->window->clear();
}

/*
 * @brief This function checks to see if the window is still running
 * @return window->isOpen()
 */
bool HelpScreen::isRunning()
{
    return this->window->isOpen();
}
