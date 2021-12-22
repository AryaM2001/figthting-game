/**
 * @brief file creates the menu interface, and will also create the game, help screen orr exit depending based on the user choice 
 */

#include "Menu.h"

/**
 * @brief for the class, creates game object and create mennu screen 
 * @param width -- the width of the window
 * @param height -- the height of the window
 */
Menu::Menu (sf::RenderWindow *window, float width, float height){

    /*variables that set the window dimensions */
    this->window = window;
    this->menuOpen = true;
    this->selectedOption = 0;
    this->width = width;
    this->height = height;

    this->setOptions();
    this->menuMusic.openFromFile("../src/audio/menuMusic.wav"); // music for the menu screen 
    this->playMusic(); //play the music 
}

/**
 * @brief Destructor of the class 
 * @param - no parameters 
 * @return Nothing 
 */
Menu::~Menu(){

}

/**
 * @brief method draw the menu text to the window (ie will draw fight, help and exit to the menu window)
 * @param - no parameters 
 * @return Nothing 
 */
void Menu::draw(){
    
    // for loop that goes through each text item and draws it to the window 
    for (int i = 0; i < TEXT_ITEMS; i++){
        this->window->draw(menu_item[i]);
    }
}

/**
 * @brief method will allow the user to move up in the menu. Also displays current text item user is on 
 * @param - No parameters
 * @return Nothing 
 */
void Menu::MoveUp()
{

    //if statement that makes sure user can move up past the first text item 
	if (selectedOption - 1 >= 0)
	{
		menu_item[selectedOption].setFillColor(sf::Color::White); //set the text to white to unhighlight the text user was on 
		selectedOption--;
		menu_item[selectedOption].setFillColor(sf::Color::Red);  //set the text user is currently on to red --> helps user know which text they are on 
	}
}

/**
 * @brief method will allow the user to move up in the menu. Also displays current text item user is on 
 * @param - No parameters
 * @return Nothing 
 */
void Menu::MoveDown()
{
     //if statement that makes sure user can move up past the last text item 
	if (selectedOption + 1 < TEXT_ITEMS)
	{
		menu_item[selectedOption].setFillColor(sf::Color::White);//set the text to white to unhighlight the text user was on 
		selectedOption++;
		menu_item[selectedOption].setFillColor(sf::Color::Red); //set the text user is currently on to red --> helps user know which text they are on 
	}
	
}


/**
 * @brief This method contains all of the logic for handling the main menu and selecting different options like launching a game, launching help screen and exiting 
 * @param - No parameters
 * @return Nothing 
 */
void Menu::update()
{
    this->window->clear();
    this->menuOpen = true;
    bool play, help, close = false; 

    //watch for which option user presses from menu
    while (this->menuOpen == true)
    {
        sf::Event event;
        
        //pop top event in queue
        while (this->window->pollEvent(event))
        {
            // swithc statements to handle the different cases the user could select 
            switch (event.type)
            {
                //upon key release
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up: //if the user click up key move up 
                        MoveUp();
                        break;

                    case sf::Keyboard::Down: //if the user clicks down key move down in the menu 
                        MoveDown();
                        break;

                    case sf::Keyboard::Return: //if the user presses enter then determine which buttone they pressed enter on 
                        switch (GetPressedItem())
                        {
                        case 0: //if GetPressedItem returns is 0 then fight button selected 
                            play = true;
                            this->menuOpen = false; //set menu to false to stop displaying menu 
                            this->menuMusic.stop(); //stop the menu music 
                            break;
                        case 1: //if GetPressedItem returns is 1 then helpscreen button selected 
                            help = true;
                            this->menuOpen = false; //set menu to false to stop displaying menu 
                            break;
                        case 2:  //if GetPressedItem returns is 2 then exit button selected 
                            close = true;
                            this->menuOpen = false; //set menu to false to stop displaying menu 
                            this->menuMusic.stop(); //stop the menu music 
                            this->window->setVisible(false); //leave the menu interface 
                            break;
                        }
                        break;
                        
                    default:
                        break;
                    }
                default:
                    break;
            }
        }
    
        //redraw buttons from menu constructor to show whats being selected
        draw();

        //render window
        this->window->display();
    }

    //if the play button is selected the player want to play the game 
    if (play == true)
    {
        // initialize game

        
        // initialize game music
        sf::Music gameMusic;
        gameMusic.openFromFile("../src/audio/gameMusic.wav");
        gameMusic.setLoop(true);
        gameMusic.play();
        gameMusic.setPlayingOffset(sf::seconds(21.5));
        gameMusic.setVolume(10);

        // map selection
        MapScreen mapscreen(this->window);

        //while loop will display map selection screen 
        while (mapscreen.mapOpen == true)
        {
            mapscreen.update();
            mapscreen.clear();
            mapscreen.draw();
        }

        //player 1 character selection 
        CharMenu char1(this->window, 1);

        //while loop will display character selection screen for player 1 
        while (char1.charOpen == true)
        {
            char1.update();
            char1.clear();
            char1.draw();
        }

        //player 2 character selection 
        CharMenu char2(this->window, 2);

        //while loop will display character selection screen for player 2
        while (char2.charOpen == true)
        {
            char2.update();
            char2.clear();
            char2.draw();
        }

        //initialize the game object and pass it the characters selected by player 1 and 2 
        Game game(this->window, char1.selectedChar, char2.selectedChar);
        game.gameOpen = true;

        // set game background based on user selection
        game.initBackground(mapscreen.selectedMap);

        // begin the game countdown
        sf::Clock clock;
        game.countdownPlaying = true;
        game.doCountdown(game.countdown);
        game.countdown--;

        //while loop that continues the game coutdown 
        while(game.countdownPlaying == true)
        {
            //if another second has passed, continue the countdown 
            if (clock.getElapsedTime().asSeconds() >= 1.0f)
            {
                game.doCountdown(game.countdown);
                game.countdown--;
                clock.restart();
            }
        }

        //while loop that displays  game interface
        while (game.gameOpen == true)
        {
            float deltaTime = clock.restart().asSeconds();
            game.update(deltaTime);

            //check if player has died and therefore is end of round
            game.checkRoundWinner(&game.player1, &game.player2);
            game.checkRoundWinner(&game.player2, &game.player1);

            game.clear();
            game.draw();

            // after this round check, check to see if the game has been decided
            game.checkGameWinner(&game.player1);
            game.checkGameWinner(&game.player2);
        }

        this->playMusic();
    }

    /* if help is true then help screen is selected by the user. Display help screen interface*/
    else if (help == true)
    {
        // initialize help menu
        HelpScreen helpscreen(this->window);

        //while loop will display help screen for users 
        while (helpscreen.helpOpen == true)
        {
            helpscreen.update();
            helpscreen.clear();
            helpscreen.draw();
        }
    }

    /* if close is true then exit is selected by the user. Close the menu and close the window */
    else if (close == true)
    {
        this->window->close(); //closes the window 
        return;
    }

    // clean up to go back to main menu
    this->setPressedItem(0);
    this->window->setVisible(true);
    this->window->requestFocus();
    this->setOptions();
    this->draw();
    this->update();

}

/**
* @brief  setter method that will sets selected option variable. Used to set selectedOption variable to fight option in the menu screen 
* @param item acts as the index postion selected option should be in 
* @return Nothing 
*/
void Menu::setPressedItem(int item)
{
    this->selectedOption = item;
}

/**
 * @brief method that is used to play the music of the menu 
 * @param - No parameters 
 * @return Nothing 
 */
void Menu::playMusic()
{
    this->menuMusic.setLoop(true);
    this->menuMusic.play();
    this->menuMusic.setPlayingOffset(sf::seconds(48.2));
    this->menuMusic.setVolume(25);
}

/**
 * @brief method that is used to intialize the menu items and set the text for Menu interface 
 * @param - No parameters 
 * @returns Nothin 
 */
void Menu::setOptions()
{
    this->font.loadFromFile("../src/arial.ttf"); //font of text 
    
    //Fight text
    this->menu_item[0].setFont(this->font); //font of text 
    this->menu_item[0].setFillColor(sf::Color::Red); //text colour is red 
    this->menu_item[0].setString("FIGHT!"); //Text 
    this->menu_item[0].setPosition(sf::Vector2f(this->width/ 2, this->height / (TEXT_ITEMS + 1) *1)); //postion of text 

    //Help text
    this->menu_item[1].setFont(this->font);//font of text 
    this->menu_item[1].setFillColor(sf::Color::White);//text colour is white 
    this->menu_item[1].setString("HELP");//Text 
    this->menu_item[1].setPosition(sf::Vector2f(this->width/ 2, this->height / (TEXT_ITEMS + 1) *2));//postion of text 

    //Exit text
    this->menu_item[2].setFont(this->font);//font of text 
    this->menu_item[2].setFillColor(sf::Color::White);//text colour is white 
    this->menu_item[2].setString("EXIT!");//Text 
    this->menu_item[2].setPosition(sf::Vector2f(this->width/ 2, this->height / (TEXT_ITEMS + 1) *3));//postion of text 
}