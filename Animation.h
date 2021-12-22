#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <map>

class Animation
{
public:
    Animation();
    ~Animation();

    void Update(float deltaTime, bool faceRight, int poses, sf::Texture *texture, float animationSpeed, std::string animation);

    sf::IntRect uvRect;

    int getCurrentImage();
private:
    sf::Vector2u imageCount;

    int currentImage;
    float totalTime;
    // float switchTime;
};

#endif