#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include <unistd.h>
#include <string> 

class Player
{

public:
    // cons / decons
    Player(int playerNumber, int mapWidth, int charSelection);
    ~Player();


    // functions
    void Update(float deltaTime);
    void Draw(sf::RenderWindow* window);
    void updateHealthBar(int playerNumber);
    int getHp();
    int getHpMax();
    void setHp(int newHp);
    bool damageEnemyHp(int *enemyHp, int change);
    void setEnemyHp(int *enemyHp);
    int* getEnemyHp();
    int* giveHealthAddress();
    sf::RectangleShape getHitbox();
    sf::RectangleShape getAttackHitbox();
    void setEnemyHitbox(sf::RectangleShape hitbox);
    sf::RectangleShape getEnemyHitbox();
    int getMapWidth();
    void setMapWidth(int width);
    void movePlayer(sf::Vector2f movement);
    bool getFaceRight();
    std::map<std::string, sf::Keyboard::Key> getKeybinds();
    int getPlayerNumber();
    void resetPlayer();
    bool isAlive;

    //vars
    sf::SoundBuffer grunt;
    sf::SoundBuffer hit;
    sf::Sound voiceSound;
    sf::Sound effectSound;
    sf::Font font;
    sf::Text hptext;

private:
    // cons / decons

    // functions
    void initAttack();
    void initHeavyAttack();
    void initJump();
    void tryDamage();

    //vars
    sf::RectangleShape body;
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBar;
    sf::RectangleShape hitbox;
    sf::RectangleShape attackHitbox;
    sf::RectangleShape enemyHitbox;
    Animation animation;
    sf::Vector2f startingPosition;
    int playerNumber;
    float jumpHeight;
    float jumpSpeed;
    float gravity;
    float speed;
    float totalTime;
    float attackTime;
    float height;
    bool faceRight;
    bool isAttacking;
    bool isHeavyAttacking;
    bool isJumping;
    bool reachedHeight;
    int hpMax;
    int curHp;
    int fullHpBarLength;
    int hpBarWidth;
    int hpBarPos[1][2];
    int *enemyHp;
    int mapWidth;
    std::map<std::string, int> poses;
    std::map<std::string, float> animSpeeds;
    std::map<std::string, sf::Texture> spriteAnimations;
    std::map<std::string, sf::Keyboard::Key> keybinds;

};

#endif