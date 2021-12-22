#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "WinnerScreen.h"


/*
 * Game glass that handles the game engine. This class contains the update and render methods to display the game to it's window private member
 */

class Game
{
private:
    void initVariables();
    void initWindow(sf::RenderWindow *window);
    void initScoreBoard();
    void attack(Player *attacker, Player *victim, int attackDamage);
    void updateScore(int player);
    void resetRound();

    // vars
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Text countDown;
    sf::Font font;
    sf::Sprite background;
    sf::Texture backgroundText;
    sf::Sprite scoreBoard;
    sf::Texture scoreboardText;
    std::map<std::string, int> attackDamages;
    sf::Vector2f lightKnockback;
    sf::Vector2f heavyKnockback;
    std::map<std::string, sf::SoundBuffer> announcerSoundsBuffers;
    std::map<std::string, sf::Sound> announcerSounds;
    sf::Text scorePlayer1;
    sf::Text scorePlayer2;
    sf::Text scoreDivider;
    int roundWinner;
    int gameWinner;
    

public:
    //cons / des
    Game(sf::RenderWindow *window, int char1Selection, int char2Selection);
    ~Game();

    //game functions
    void pollEvents();
    void clear();
    void update(float deltaTime);
    void render();
    void draw();
    sf::RenderWindow* getWindow();
    void doCountdown(float count);
    void initBackground(int index);
    void drawBackground();
    void drawScoreboard();
    void checkRoundWinner(Player *attacker, Player *victim);
    void showRoundWinner(int playerNumber);
    void checkGameWinner(Player *player);
    void showGameWinner(int playerNumber);

    //game vars
    Player player1, player2;
    float countdown;
    bool isSelectingMap;
    bool gameOpen;
    bool countdownPlaying;
    int scoreP1;
    int scoreP2;

};

#endif