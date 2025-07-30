#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Animation.h"
#include "../include/Collision.h"

class Object {
private:
    sf::RectangleShape body;
    sf::RectangleShape hitbox;

    bool showHitbox;

    Collision collision;

public:
    Object(sf::Vector2f h_size, sf::Vector2f t_size, sf::Vector2f pos, sf::Texture* txtr, bool showHitbox);
    ~Object();

    void draw(sf::RenderWindow& win);
    Collision& getCollider() { return collision; }
};
