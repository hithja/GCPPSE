#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/Collision.h"

Collision::Collision(sf::RectangleShape& body) : body(body) {}

Collision::~Collision() {}

bool Collision::checkCollision(Collision& other, sf::Vector2f& direction, float force) {
    sf::Vector2f otherPos = other.getPos();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPos = getPos();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPos.x - thisPos.x;
    float deltaY = otherPos.y - thisPos.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        force = std::min(std::max(force, 0.0f), 1.0f);

        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                move(intersectX * (1.0f - force), 0.0f);
                other.move(-intersectX * force, 0.0f);

                direction.x = 1.0f;
                direction.y = 0.0f;
            }
            else {
                move(-intersectX * (1.0f - force), 0.0f);
                other.move(intersectX * force, 0.0f);

                direction.x = -1.0f;
                direction.y = 0.0f;
            }
        }
        else {
            if (deltaY > 0.0f) {
                move(0.0f, intersectY * (1.0f - force));
                other.move(0.0f, -intersectY * force);

                direction.x = 0.0f;
                direction.y = 1.0f;
            }
            else {
                move(0.0f, -intersectY * (1.0f - force));
                other.move(0.0f, intersectY * force);

                direction.x = 0.0f;
                direction.y = -1.0f;
            }
        }

        return true;
    }

    return false;
}