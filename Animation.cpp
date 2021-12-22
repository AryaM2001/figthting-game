/*
 * This class represnts the animations the players can utulize
 */

#include "Animation.h"

/*
 * Constructor for the animations, initializes some important animation variables 
 */
Animation::Animation()
{
    this->totalTime = 0.0f;
    this->currentImage = 0;
}

/*
 * Destructor
 */
Animation::~Animation()
{   
}

/*
 * This function handles the logic that handles player behaviour. This includes changes the animation image frame, and determining direction the player is facing
 */
void Animation::Update(float deltaTime, bool faceRight, int poses, sf::Texture *texture, float animationSpeed, std::string action)
{

    totalTime += deltaTime;

    if(totalTime >= animationSpeed)
    {
        totalTime -= animationSpeed;
        currentImage++;

        if (currentImage >= poses && action == "die")
        {
            currentImage = 3;
        }
        else if (currentImage >= poses)
        {
            currentImage = 0;
        }
    }

    //set width and height of each sprite pose
    uvRect.width = texture->getSize().x / float(poses); // width of sprite = textureWidthPixels / # of animation images per row (this will change)
    uvRect.height = texture->getSize().y;               // height of sprite = textureHeightPixels (should be 82 based on current sprites picked)
    uvRect.top = 0;

    //since sprites by default are facing right, need to do some logic to flip the pose if player is moving left. only do this if player is alive
    if (faceRight)
    {
            uvRect.left = currentImage * uvRect.width;
            uvRect.width = abs(uvRect.width);
    }
    else
    {
            uvRect.left = (currentImage + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
    }
}

int Animation::getCurrentImage()
{
    return this->currentImage;
}