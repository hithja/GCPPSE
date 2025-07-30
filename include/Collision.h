#pragma once
#include <SFML/Graphics.hpp>

class Collision {
private:
    sf::RectangleShape& body;
public:
    Collision(sf::RectangleShape& body);
    ~Collision();

    void move(float dx, float dy) { body.move(dx, dy); }

    bool checkCollision (Collision& other, sf::Vector2f& direction, float force);
    sf::Vector2f getPos() { return body.getPosition(); }
    sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }
};
