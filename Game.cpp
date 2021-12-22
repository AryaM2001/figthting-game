/*
 * This class represents the actual game that can be played
 */
#include "Game.h"


// Initialization functions
/*
 * This function watches the game variables
 */
void Game::initVariables()
{
    this->window = nullptr;
}


/*
 * This function initializes the game window
 */
void Game::initWindow(sf::RenderWindow *window)
{
    this->window = window;
}

void Game::initBackground(int index)
{
    if (index == 0)
    {
        if (!this->backgroundText.loadFromFile("../src/Background/background.jpeg"))
        {
            printf("Error loading background");
        }
        this->background.setTexture(this->backgroundText);
    }
    else if (index == 1)
    {
        if (!this->backgroundText.loadFromFile("../src/Background/lava.jpg"))
        {
            printf("Error loading background");
        }
        this->background.setTexture(this->backgroundText);
    }
    
}

void Game::initScoreBoard()
{
    if (!this->scoreboardText.loadFromFile("../src/sprites/scoreboard/ScoreboardHolder.jpg"))
    {
        printf("Error loading scoreboard");
    }
    this->scoreBoard.setTexture(this->scoreboardText);
    this->scoreBoard.setPosition(this->window->getSize().x/2 - this->scoreBoard.getLocalBounds().width/2, 10);
}

/*
 * This function is the constructor and also initializes game variables and the game window 
 */
Game::Game(sf::RenderWindow *window, int char1Selection, int char2Selection): 
    player1(1, window->getSize().x,  char1Selection), player2(2, window->getSize().x, char2Selection)
{
    this->initVariables();
    this->initWindow(window);

    //countdown
    this->font.loadFromFile("../src/KaushanScript.otf");
    this->countDown.setFont(font);
    this->countDown.setCharacterSize(250);
    this->countDown.setStyle(sf::Text::Bold);

    this->countDown.setPosition(this->window->getSize().x/2 - this->countDown.getLocalBounds().width/2, 230.0f);
    this->countdown = 4.0f;

    // countdown announcer audio
    this->announcerSoundsBuffers["3"] = sf::SoundBuffer();
    this->announcerSoundsBuffers.find("3")->second.loadFromFile("../src/audio/announcer3.wav");
    this->announcerSounds["3"] = sf::Sound();
    this->announcerSounds.find("3")->second.setBuffer(this->announcerSoundsBuffers.find("3")->second);

    this->announcerSoundsBuffers["2"] = sf::SoundBuffer();
    this->announcerSoundsBuffers.find("2")->second.loadFromFile("../src/audio/announcer2.wav");
    this->announcerSounds["2"] = sf::Sound();
    this->announcerSounds.find("2")->second.setBuffer(this->announcerSoundsBuffers.find("2")->second);

    this->announcerSoundsBuffers["1"] = sf::SoundBuffer();
    this->announcerSoundsBuffers.find("1")->second.loadFromFile("../src/audio/announcer1.wav");
    this->announcerSounds["1"] = sf::Sound();
    this->announcerSounds.find("1")->second.setBuffer(this->announcerSoundsBuffers.find("1")->second);

    this->announcerSoundsBuffers["go"] = sf::SoundBuffer();
    this->announcerSoundsBuffers.find("go")->second.loadFromFile("../src/audio/announcergo.wav");
    this->announcerSounds["go"] = sf::Sound();
    this->announcerSounds.find("go")->second.setBuffer(this->announcerSoundsBuffers.find("go")->second);

    player1.setMapWidth(int(this->window->getSize().x));
    player2.setMapWidth(int(this->window->getSize().x));
    player1.setEnemyHp(player2.giveHealthAddress());
    player2.setEnemyHp(player1.giveHealthAddress());

    player1.setEnemyHitbox(player2.getHitbox());
    player2.setEnemyHitbox(player1.getHitbox());

    //ingame variables like attack damage, knockback, etc
    this->attackDamages["attack1"] = -10;
    this->attackDamages["attack2"] = -25;

    this->lightKnockback.x = 90.0f;
    this->lightKnockback.y = -30.0f;
    this->heavyKnockback.x = 150.0f;
    this->heavyKnockback.y = -75.0f;

    this->initScoreBoard();

    this->scoreP1 = 0;
    this->scoreP2 = 0;

    //sets the text for the scoreboard
    this->scorePlayer1.setFont(font);
    this->scorePlayer1.setString(std::to_string(scoreP1));
    this->scorePlayer1.setCharacterSize(55);
    this->scorePlayer1.setPosition(this->window->getSize().x/2 - this->scoreBoard.getLocalBounds().width/4, 40.0f);
    this->scorePlayer1.setFillColor(sf::Color::White);
    this->scorePlayer1.setStyle(sf::Text::Bold);

    this->scorePlayer2.setFont(font);
    this->scorePlayer2.setString(std::to_string(scoreP2));
    this->scorePlayer2.setCharacterSize(55);
    this->scorePlayer2.setPosition(this->window->getSize().x/2 + this->scoreBoard.getLocalBounds().width/4 - this->scorePlayer2.getLocalBounds().width, 40.0f);
    this->scorePlayer2.setFillColor(sf::Color::White);
    this->scorePlayer2.setStyle(sf::Text::Bold);

    this->scoreDivider.setFont(font);
    this->scoreDivider.setString(":");
    this->scoreDivider.setCharacterSize(55);
    this->scoreDivider.setPosition(this->window->getSize().x/2 - this->scoreDivider.getLocalBounds().width/2, 40.0f);
    this->scoreDivider.setFillColor(sf::Color::White);
    this->scoreDivider.setStyle(sf::Text::Bold);

}

/*
 * Destructor
 */
Game::~Game()
{
}

/*
 * This function watches the game and listen for game events
 * Check for any events happening. These will include checking for user input and windows close events
*/
void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            // window close
            case sf::Event::Closed:
            {
                this->window->close();
                break;
            }
            // keybind events
            case sf::Event::KeyPressed:
            {
                //player 1 keybind events----------------
                if(ev.key.code == player1.getKeybinds().find("attack1")->second)
                {
                    this->attack(&player1, &player2, this->attackDamages.find("attack1")->second);
                }
                if(ev.key.code == player1.getKeybinds().find("attack2")->second)
                {
                    this->attack(&player1, &player2, this->attackDamages.find("attack2")->second);
                }


                //Player 2 keybind events-----------------
                if(ev.key.code == player2.getKeybinds().find("attack1")->second)
                {
                    this->attack(&player2, &player1, this->attackDamages.find("attack1")->second);
                }
                if(ev.key.code == player2.getKeybinds().find("attack2")->second)
                {
                    this->attack(&player2, &player1, this->attackDamages.find("attack2")->second);
                }
            }

            default:
                break;
        }
            
        //Game Exit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && gameOpen == true)
        {
            this->gameOpen = false;
        }
    }
}

void Game::clear(){
    this->window->clear(sf::Color::Black);
}


/*
 * This function watches the gaem and listen for game events 
 */
void Game::update(float deltaTime)
{   
    //update players
    this->player1.Update(deltaTime);
    this->player2.Update(deltaTime);

    //check if event has occured 
    this->pollEvents();

}

void Game::checkRoundWinner(Player *attacker, Player *victim)
{
    if (victim->isAlive == false)
    {
        this->roundWinner = attacker->getPlayerNumber();
        this->updateScore(roundWinner);
        this->clear();
        this->draw();
        this->showRoundWinner(roundWinner);
        this->resetRound();
    }
}

/*
 * This function sends information to the WinnerScreen to display who won the round
 * This is displayed for 3 seconds
 * @param playerNumber
 */
void Game::showRoundWinner(int playerNumber)
{
        sf::Clock timer;
        bool showingRoundWinner = true;
        WinnerScreen win(this->window, playerNumber, "round");
        while(showingRoundWinner == true)
        {
            // gui to display round winner goes here
            win.draw();
            if(timer.getElapsedTime().asSeconds() >= 3.0f){
                showingRoundWinner = false;
            }
        }
}

/*
 * This function sends information to the WinnerScreen to display who won the game
 * The WinnerScreen is displayed on screen for 3 seconds
 * @param playerNumber
 */
void Game::showGameWinner(int playerNumber)
{
        sf::Clock timer;
        bool showingGameWinner = true;
        WinnerScreen win(this->window, playerNumber, "game");
        while(showingGameWinner == true)
        {
            // gui to display game winner goes here
            win.clear();
            win.draw();
            if(timer.getElapsedTime().asSeconds() >= 3.0f){

                showingGameWinner = false;
            }
        }
}

void Game::resetRound()
{
    this->player1.resetPlayer();
    this->player2.resetPlayer();
}

/*
 * This function renders anything currently drawn to the window
 */

void Game::draw()
{
    this->window->draw(background);
    this->window->draw(scoreBoard);
    this->window->draw(scoreDivider);
    this->window->draw(scorePlayer1);
    this->window->draw(scorePlayer2);
    this->player1.Draw(this->window);
    this->player2.Draw(this->window);

    this->window->display();
}

/*
 * this function returns the game window
 */
sf::RenderWindow* Game::getWindow(){
    return this->window;
}

void Game::doCountdown(float count)
{
    this->window->clear();

    if (count == 4.0f)
    {
        this->countDown.setString("3");
        this->announcerSounds.find("3")->second.play();
        this->countDown.setPosition(this->window->getSize().x/2 - this->countDown.getLocalBounds().width/2, 230.0f);
    }

    else if (count == 3.0f)
    {
        this->countDown.setString("2");
        this->announcerSounds.find("2")->second.play();
        this->countDown.setPosition(this->window->getSize().x/2 - this->countDown.getLocalBounds().width/2, 230.0f);
    }

    else if (count == 2.0f)
    {
        this->countDown.setString("1");
        this->announcerSounds.find("1")->second.play();
        this->countDown.setPosition(this->window->getSize().x/2 - this->countDown.getLocalBounds().width/2, 230.0f);
    }

    else if (count == 1.0f)
    {
        this->countDown.setString("GO");
        this->announcerSounds.find("go")->second.play();
        this->countDown.setPosition(this->window->getSize().x/2 - this->countDown.getLocalBounds().width/2, 230.0f);
    }

    else if (count == 0.0f)
    {
        this->countdownPlaying = false;
        return;
    }

    this->window->draw(this->countDown);
    this->window->display();   
}

void Game::attack(Player *attacker, Player *victim, int attackDamage)
{
    //play sounds
    attacker->voiceSound.play();
    attacker->effectSound.play();

    //update attack hitbox to match range of attack
    attacker->getAttackHitbox().setSize(sf::Vector2f(50.0f, 85.0f));

    //if potential victim's hitbox is in the attack range, damage victim
    if (attacker->getAttackHitbox().getGlobalBounds().intersects(victim->getHitbox().getGlobalBounds()))
    {
        // damage enemy
        attacker->damageEnemyHp(attacker->getEnemyHp(), attackDamage);

        // knockback enemy
        if (attacker->getFaceRight() == true)
            victim->movePlayer(sf::Vector2f(this->heavyKnockback.x,this->heavyKnockback.y));
        else
            victim->movePlayer(sf::Vector2f(-this->heavyKnockback.x,this->heavyKnockback.y));
    }
}

void Game::updateScore(int player)
{
    if(player == 1) //player 1
    {
        this->scoreP1 = this->scoreP1 + 1;
        this->scorePlayer1.setString(std::to_string(this->scoreP1));
    }
    else //player 2
    {
        this->scoreP2 = this->scoreP2 + 1;
        this->scorePlayer2.setString(std::to_string(this->scoreP2));  
    }  

}

void Game::checkGameWinner(Player *player)
{
    if (player->getPlayerNumber() == 1)
    {
        if (this->scoreP1 == 4)
        {
            // set game winner to use to display game winner screen
            this->gameWinner = player->getPlayerNumber();

            // show game winner screen
            this->showGameWinner(roundWinner);

            // end the game and return to main menu
            this->gameOpen = false;
        }
    }
    else if (player->getPlayerNumber() == 2)
    {
        if (this->scoreP2 == 4)
        {
            // set game winner to use to display game winner screen
            this->gameWinner = player->getPlayerNumber();

            // show game winner screen
            this->showGameWinner(roundWinner);

            // end the game and return to main menu
            this->gameOpen = false;
        }
    }
    
}
