#include <SFML/Graphics.hpp>
#include "../include/Animation.h"

Animation::Animation(sf::Texture* txtr, sf::Vector2u imgCount, float switchTime) {
    this->imgCount = imgCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currImg.x = 0;

    uvRect.width = txtr->getSize().x / float(imgCount.x);
    uvRect.height = txtr->getSize().y / float(imgCount.y);
}

Animation::~Animation() {}

void Animation::update(int row, float deltaTime, bool faceRight) {
    currImg.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currImg.x++;

        if (currImg.x >= imgCount.x) {
            currImg.x = 0;
        }
    }

    uvRect.top = currImg.y * uvRect.height;

    if (faceRight) {
        uvRect.left = currImg.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else {
        uvRect.left = (currImg.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}