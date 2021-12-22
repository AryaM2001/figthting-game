/*
 * This class represnts the player object in a game
 */

#include "Player.h"



/*
 * Contsturctor for the players. Initializes player variables and places them in the correct locations
 */
Player::Player(int playerNumber, int mapWidth, int charSelection) :
    animation()
{
    this->playerNumber = playerNumber;
    this->jumpHeight = 250.0f;
    this->jumpSpeed = 6.0f;
    this->gravity = 2.0f;
    this->speed = 300.0f;
    this->totalTime = 0.0f;
    this->attackTime = 0.0f;
    this->faceRight = true;
    this->isAttacking = false;
    this->isHeavyAttacking = false;
    this->isJumping = false;
    this->reachedHeight = false;
    this->hpMax = 100;
    this->curHp = 100;
    this->fullHpBarLength = 625;
    this->hpBarWidth = 70;
    this->enemyHp = nullptr;
    this->isAlive = true;

    this->mapWidth = mapWidth;

    // logic dependant on playerNumber (starting position, sprites, etc)
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture jumpTexture;
    sf::Texture attack1Texture;
    sf::Texture attack2Texture;
    sf::Texture dieTexture;

    // initialize hitboxes and body size now as we will need their sizes during initialization
    this->body.setSize(sf::Vector2f(320.0f, 192.0f));
    this->hitbox.setSize(sf::Vector2f(50.0f, 124.0f));

    if (playerNumber == 1)
    {
        if(charSelection == 0){
            // Wizard  animations
            idleTexture.loadFromFile("../src/sprites/Player1/Player1WizIdle.png");
            runTexture.loadFromFile("../src/sprites/Player1/Player1WizRun.png");
            attack1Texture.loadFromFile("../src/sprites/Player1/Player1WizAttack1.png");
            attack2Texture.loadFromFile("../src/sprites/Player1/Player1WizAttack2.png");
            jumpTexture.loadFromFile("../src/sprites/Player1/Player1WizJump.png");
            dieTexture.loadFromFile("../src/sprites/Player1/Player1WizDie.png");
        }

        else{
            idleTexture.loadFromFile("../src/sprites/Player1/Idle.png");
            runTexture.loadFromFile("../src/sprites/Player1/Run.png");
            attack1Texture.loadFromFile("../src/sprites/Player1/Attack1.png");
            attack2Texture.loadFromFile("../src/sprites/Player1/Attack2.png");
            jumpTexture.loadFromFile("../src/sprites/Player1/Jump.png");
            dieTexture.loadFromFile("../src/sprites/Player1/Die.png");
        }

        startingPosition.x = this->mapWidth/2 - this->mapWidth/4;
        startingPosition.y = 540.0f;

        //player 1 animation speeds
        this->animSpeeds["idle"] = 0.075f;
        this->animSpeeds["run"] = 0.05f;
        this->animSpeeds["attack1"] = 0.040f;
        this->animSpeeds["attack2"] = 0.040f;
        this->animSpeeds["jump"] = 0.075f;
        this->animSpeeds["die"] = 0.075f;

        // player 1 number of poses (or frames) for each animation
        this->poses["idle"] = 1;
        this->poses["run"] = 8;
        this->poses["attack1"] = 15;
        this->poses["attack2"] = 8;
        this->poses["jump"] = 1;
        this->poses["die"] = 4;

        // set keybinds
        this->keybinds["moveLeft"] = sf::Keyboard::A;
        this->keybinds["moveRight"] = sf::Keyboard::D;
        this->keybinds["attack1"] = sf::Keyboard::Q;
        this->keybinds["attack2"] = sf::Keyboard::E;
        this->keybinds["jump"] = sf::Keyboard::W;

        //position of player health bar
        this->healthBarBack.setSize(sf::Vector2f(fullHpBarLength, hpBarWidth));
        this->hpBarPos[0][0] = 40.0f;;
        this->hpBarPos[0][1] = 40;
        this->healthBarBack.setFillColor(sf::Color::Red);
        this->healthBarBack.setPosition(sf::Vector2f(hpBarPos[0][0], hpBarPos[0][1]));

        //setting up the text under the healthbars 
        this->font.loadFromFile("../src/KaushanScript.otf");
        this->hptext.setFont(font);
        this->hptext.setString("Player 1");
        this->hptext.setCharacterSize(55);
        this->hptext.setPosition(60.0f, 42.0f);
        this->hptext.setFillColor(sf::Color::Yellow);
        this->hptext.setStyle(sf::Text::Bold);
        this->hptext.setOutlineColor(sf::Color::Red);
        this->hptext.setOutlineThickness(5.0f);
        
    }
    else
    {
        if(charSelection == 0){
            // Wizard  animations
            idleTexture.loadFromFile("../src/sprites/Player2/Player2WizIdle.png");
            runTexture.loadFromFile("../src/sprites/Player2/Player2WizRun.png");
            attack1Texture.loadFromFile("../src/sprites/Player2/Player2WizAttack1.png");
            attack2Texture.loadFromFile("../src/sprites/Player2/Player2WizAttack2.png");
            jumpTexture.loadFromFile("../src/sprites/Player2/Player2WizJump.png");
            dieTexture.loadFromFile("../src/sprites/Player2/Player2WizDie.png");
        }

        else{
            idleTexture.loadFromFile("../src/sprites/Player2/Idle.png");
            runTexture.loadFromFile("../src/sprites/Player2/Run.png");
            attack1Texture.loadFromFile("../src/sprites/Player2/Attack1.png");
            attack2Texture.loadFromFile("../src/sprites/Player2/Attack2.png");
            jumpTexture.loadFromFile("../src/sprites/Player2/Jump.png");
            dieTexture.loadFromFile("../src/sprites/Player2/Die.png");
        }
        startingPosition.x = this->mapWidth/2 + this->mapWidth/4 - this->body.getSize().x;
        startingPosition.y = 540.0f;

        //player 2 animation speeds
        this->animSpeeds["idle"] = 0.075f;
        this->animSpeeds["run"] = 0.075f;
        this->animSpeeds["attack1"] = 0.040f;
        this->animSpeeds["attack2"] = 0.040f;
        this->animSpeeds["jump"] = 0.075f;
        this->animSpeeds["die"] = 0.075f;

        // player 2 number of poses (or frames) for each animation
        this->poses["idle"] = 1;
        this->poses["run"] = 8;
        this->poses["attack1"] = 15;
        this->poses["attack2"] = 8;
        this->poses["jump"] = 1;
        this->poses["die"] = 4;

        // set keybinds
        this->keybinds["moveLeft"] = sf::Keyboard::Left;
        this->keybinds["moveRight"] = sf::Keyboard::Right;
        this->keybinds["attack1"] = sf::Keyboard::Slash;
        this->keybinds["attack2"] = sf::Keyboard::Period;
        this->keybinds["jump"] = sf::Keyboard::Up;

        //position of player 2 health bar
        this->healthBarBack.setSize(sf::Vector2f(fullHpBarLength, hpBarWidth));
        this->hpBarPos[0][0] = this->mapWidth - this->healthBarBack.getLocalBounds().width - 40.0f;;
        this->hpBarPos[0][1] = 40;
        this->healthBarBack.setFillColor(sf::Color::Red);
        this->healthBarBack.setPosition(sf::Vector2f(hpBarPos[0][0], hpBarPos[0][1]));

        //setting up the text under the healthbars
        this->font.loadFromFile("../src/KaushanScript.otf"); 
        this->hptext.setFont(font);
        this->hptext.setString("Player 2");
        this->hptext.setCharacterSize(55);
        this->hptext.setPosition(this->mapWidth - this->healthBarBack.getLocalBounds().width - 20.0f, 42.0f);
        this->hptext.setFillColor(sf::Color::Yellow);
        this->hptext.setStyle(sf::Text::Bold);
        this->hptext.setOutlineColor(sf::Color::Red);
        this->hptext.setOutlineThickness(5.0f);

        this->faceRight = false;
    }


    // add textures to list
    this->spriteAnimations["idle"] = idleTexture;
    this->spriteAnimations["run"] = runTexture;
    this->spriteAnimations["jump"] = jumpTexture;
    this->spriteAnimations["attack1"] = attack1Texture;
    this->spriteAnimations["attack2"] = attack2Texture;
    this->spriteAnimations["die"] = dieTexture;

    //default body position and size
    this->body.setPosition(startingPosition);
    this->body.setTexture(&idleTexture);

    //set hitbox to the centered position on body
    float centerX = this->body.getPosition().x + (this->body.getSize().x / 2) - (this->hitbox.getSize().x / 2);
    float centerY = this->body.getPosition().y + (this->hitbox.getSize().y / 2) + 5.0f;
    this->hitbox.setPosition(sf::Vector2f(centerX,centerY));
    this->hitbox.setFillColor(sf::Color::Transparent);

    // set attack hitbox to appropriate side of the body
    this->attackHitbox.setSize(sf::Vector2f(100.0f, 124.0f));
    if (faceRight == true)
        centerX = this->hitbox.getPosition().x + this->hitbox.getSize().x;
    else
        centerX = this->hitbox.getPosition().x - this->attackHitbox.getSize().x;
    this->attackHitbox.setPosition(centerX, centerY);
    this->attackHitbox.setFillColor(sf::Color::Transparent);

    // load player sound files
    this->grunt.loadFromFile("../src/audio/Player1/attack1grunt.wav");
    this->hit.loadFromFile("../src/audio/Player1/attack1hit.wav");
    this->voiceSound.setBuffer(this->grunt);
    this->effectSound.setBuffer(this->hit);
    this->voiceSound.setVolume(20.0f);
    this->effectSound.setVolume(20.0f);
    
}

/*
 * Destructor
 */
Player::~Player()
{
}

/*
 * Methods related to health bar values
 */
int Player::getHpMax() {
    return this->hpMax;
}

int Player::getHp() {
    return this->curHp;
}

void Player::setHp(int newHp){
    this->curHp = newHp;
}

int* Player::getEnemyHp()
{
    return this->enemyHp;
}

bool Player::damageEnemyHp(int *enemyHp, int change)
{
    //if the hp changes to somewhere within the accepted range, increase it TO the max
    if(*enemyHp + change < this->hpMax && *enemyHp + change >= 0){
        *enemyHp += change;
    }
    //if hp drops below 0, return false. Change return to exit screen
    else if(*enemyHp + change <= 0){
        *enemyHp = 0;
        return false;
    }
    else{
        *enemyHp = this->hpMax;
    }
    return true;
}

/*
 * This function handles the logic that handles player behaviour. This includes movement input, health changes, etc.
 */
void Player::Update(float deltaTime)
{
    //initialize movement and action variables
    std::string action = "run";
    sf::Vector2f movement(0.0F, 0.0F);

    // if player is dead, stop their horizontal movement, let gravity be applied, and dont allow any other actions
    if (this->curHp <= 0)
    {
        movement.y = 0.0f;
        movement.x = 0.0f;
        action = "die";
        if (this->body.getPosition().y < this->startingPosition.y)
        {
            movement.y += this->gravity * speed * deltaTime;
        }
    }
    else
    {
        // jumping
        if (this->body.getPosition().y > this->startingPosition.y)
        {
            this->isJumping = false;
            this->reachedHeight = false;
        }

        // basic movement check
        if (sf::Keyboard::isKeyPressed(keybinds["attack1"]) && this->isAttacking == false && this->isHeavyAttacking == false)
        {
            initAttack();
        }

        // basic movement check
        if (sf::Keyboard::isKeyPressed(keybinds["attack2"]) && this->isAttacking == false && this->isHeavyAttacking == false)
        {
            initHeavyAttack();
        }

        if (sf::Keyboard::isKeyPressed(keybinds["jump"]) && this->isJumping == false)
        {
            initJump();
        }

        if (sf::Keyboard::isKeyPressed(keybinds["moveLeft"]))
        {
            movement.x -= speed * deltaTime;
            faceRight = false;
        }

        if (sf::Keyboard::isKeyPressed(keybinds["moveRight"]))
        {
            movement.x += speed * deltaTime;
            faceRight = true;
        }

        // action checks
        // idle
        if (movement.x == 0 && this->isAttacking == false && this->isHeavyAttacking == false)
        {
            action = "idle";
        }

        //Determine if the character is not in the bounds of the screen -- if true -- redraw character within the bounds
        if (this->hitbox.getPosition().x < 0)
        { //Check the left bound
            body.setPosition(0 - (this->body.getSize().x / 2) + 25.0f, this->body.getPosition().y);
            hitbox.setPosition(this->body.getPosition().x + (this->body.getSize().x / 2) - (this->hitbox.getSize().x / 2), hitbox.getPosition().y);
        }

        if (this->hitbox.getPosition().x + this->hitbox.getSize().x > this->getMapWidth())
        { //Check the right bound
            body.setPosition(this->getMapWidth() - (this->body.getSize().x / 2) - 25.0f, this->body.getPosition().y);
            hitbox.setPosition(this->getMapWidth() - this->hitbox.getSize().x, hitbox.getPosition().y);
        }

        // if player is just in the air because they got attacked, then just apply gravity
        if (this->isJumping == false && this->body.getPosition().y < this->startingPosition.y)
        {
            movement.y += this->gravity * speed * deltaTime;
        }

        if (this->isJumping == true)
        {
            // check if player has reached max jump height
            if (this->hitbox.getPosition().y < this->height)
            {
                this->reachedHeight = true;
            }

            // if they havent, then player is in climb of jump, so move them upwards
            if (this->reachedHeight == false)
            {
                movement.y -= this->jumpSpeed * speed * deltaTime;
            }

            // if they have, then player is now in descent of jump, so move them downwards
            else if (this->reachedHeight == true)
            {
                movement.y += this->gravity * speed * deltaTime;
            }
            movement.x = movement.x * 1.8;
            action = "jump";
        }

        // attacking
        if (this->isAttacking == true)
        {
            if (this->totalTime - this->attackTime > 250.0f)
            {
                this->isAttacking = false;
                this->attackTime = 0.0f;
            }
            else
            {
                action = "attack1";
            }
        }

        if (this->isHeavyAttacking == true)
        {
            if (this->totalTime - this->attackTime > 250.0f)
            {
                this->isHeavyAttacking = false;
                this->attackTime = 0.0f;
            }
            else
            {
                action = "attack2";
            }
        }

        //facing right (need to change side that attacking hitbox is on).
        if (faceRight == true)
        {
                this->attackHitbox.setPosition(
                    this->hitbox.getPosition().x + this->hitbox.getSize().x,
                    this->body.getPosition().y + (this->hitbox.getSize().y / 2) + 5.0f);
        }
        else
        {
                this->attackHitbox.setPosition(
                    this->hitbox.getPosition().x - this->attackHitbox.getSize().x,
                    this->body.getPosition().y + (this->hitbox.getSize().y / 2) + 5.0f);
        }
    }

    // update health
    this->updateHealthBar(this->playerNumber);

    // update hitbox and body textures based on movement and action 
    this->body.setTexture(&spriteAnimations[action]);
    this->animation.Update(deltaTime, faceRight, poses[action], &spriteAnimations[action],animSpeeds[action], action);
    
    // wait for death animation to finish before game declares player as "dead"
    if (action == "die" && this->animation.getCurrentImage() == 3 && this->body.getPosition().y >= this->startingPosition.y)
        this->isAlive = false;
    this->body.setTextureRect(animation.uvRect);
    movePlayer(movement);

    this->totalTime++;
}


void Player::movePlayer(sf::Vector2f movement)
{
    this->body.move(movement);
    this->hitbox.move(movement);
    this->attackHitbox.move(movement);
}

bool Player::getFaceRight()
{
    return this->faceRight;
}

/*
 * This function updates the player healthbar
 */
void Player::updateHealthBar(int playerNumber)
{   
    if (playerNumber == 1)
    {
    //healthbar for player 1
    float healthPercent = curHp / static_cast< float >(this->hpMax);
    int currentHealth = static_cast< int >(fullHpBarLength * healthPercent);
    this->healthBarBack.setFillColor(sf::Color::Red);

    this->healthBar.setSize(sf::Vector2f(currentHealth, hpBarWidth));
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setPosition(sf::Vector2f(hpBarPos[0][0], hpBarPos[0][1]));
    }

    else if (playerNumber == 2)
    {
    //healthbar for player 2
    float healthPercent = curHp / static_cast< float >(this->hpMax);
    int currentHealth = static_cast< int >(fullHpBarLength * healthPercent);
    this->healthBarBack.setFillColor(sf::Color::Red);

    this->healthBar.setSize(sf::Vector2f(currentHealth, hpBarWidth));
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setPosition(sf::Vector2f(hpBarPos[0][0], hpBarPos[0][1]));
    }
}

/*
 * This function renders the player to the game window
 */
void Player::Draw(sf::RenderWindow* window)
{
    window->draw(healthBarBack);
    window->draw(healthBar);
    window->draw(body);
    window->draw(hitbox);
    window->draw(attackHitbox);
    window->draw(hptext);
}
void Player::initAttack()
{
    // set bools and keep track of attack time
    this->isAttacking = true;
    this->attackTime = this->totalTime;
    
}

void Player::initHeavyAttack()
{
    // set bools and keep track of attack time
    this->isHeavyAttacking = true;
    this->attackTime = this->totalTime;  
}

void Player::tryDamage()
{
    // if(this->attackHitbox.getGlobalBounds().intersects(this->enemyHitbox.getGlobalBounds()))
    // {
    //     damageEnemyHp(this->enemyHp, -10);
    // }
}

void Player::initJump()
{
    // sf::Vector2f jump(0.0F, -this->jumpHeight);
    // this->body.move(jump);
    // this->hitbox.move(jump);
    // this->attackHitbox.move(jump);
    this->isJumping = true;
    this->reachedHeight = false;
    this->height = this->hitbox.getPosition().y - this->jumpHeight;
}

int* Player::giveHealthAddress(){
    return &this->curHp;
}

void Player::setEnemyHp(int *enemy)
{
    this->enemyHp = enemy;
}

sf::RectangleShape Player::getHitbox(){
    return this->hitbox;
}

sf::RectangleShape Player::getAttackHitbox(){
    return this->attackHitbox;
}

void Player::setEnemyHitbox(sf::RectangleShape hitbox){
    this->enemyHitbox = hitbox;
}

sf::RectangleShape Player::getEnemyHitbox(){
    return this->enemyHitbox;
}

int Player::getMapWidth()
{
    return this->mapWidth;
}

void Player::setMapWidth(int width)
{
    this->mapWidth = width;
}

int Player::getPlayerNumber()
{
    return this->playerNumber;
}

void Player::resetPlayer()
{
    // reset direction sprite is facing
    if (this->playerNumber == 1)
        this->faceRight = true;
    else if (this->playerNumber == 2)
        this->faceRight = false;

    // reset body
    this->body.setPosition(startingPosition);

    // reset hitbox
    float centerX = this->body.getPosition().x + (this->body.getSize().x / 2) - (this->hitbox.getSize().x / 2);
    float centerY = this->body.getPosition().y + (this->hitbox.getSize().y / 2) + 5.0f;
    this->hitbox.setPosition(sf::Vector2f(centerX,centerY));

    // reset attackbox
    if (faceRight == true)
        centerX = this->hitbox.getPosition().x + this->hitbox.getSize().x;
    else
        centerX = this->hitbox.getPosition().x - this->attackHitbox.getSize().x;
    this->attackHitbox.setPosition(centerX, centerY);

    // reset player health and health bar
    this->curHp = 100;
    this->isAlive = true;
    this->updateHealthBar(this->playerNumber);

}

std::map<std::string, sf::Keyboard::Key> Player::getKeybinds()
{
    return this->keybinds;
}