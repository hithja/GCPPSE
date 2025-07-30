#pragma once
#include <SFML/Graphics.hpp>

class Animation {
private:
    sf::Vector2u imgCount;
    sf::Vector2u currImg;

    float totalTime;
    float switchTime;
public:
    Animation(sf::Texture* txtr, sf::Vector2u imgCount, float switchTime);
    ~Animation();

    void update(int row, float deltaTime, bool faceRight);

    sf::IntRect uvRect;
};
