#include <SFML/Graphics.hpp>
#include "../include/Animation.h"
#include "../include/Collision.h"
#include "../include/Object.h"

Object::Object(sf::Vector2f h_size, sf::Vector2f t_size, sf::Vector2f pos, sf::Texture* txtr, bool showHitbox) : collision(hitbox) {
    this->showHitbox = showHitbox;

    hitbox.setSize(h_size);
    hitbox.setOrigin(hitbox.getSize() / 2.0f);
    hitbox.setPosition(pos);

    if (showHitbox) {
        hitbox.setFillColor(sf::Color::Red);
    }
    else {
        hitbox.setFillColor(sf::Color::Transparent);
    }

    body.setSize(t_size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(txtr);
    body.setPosition(hitbox.getPosition());
}

Object::~Object() {
}

void Object::draw(sf::RenderWindow& win) {
    win.draw(hitbox);
    body.setPosition(hitbox.getPosition());
    win.draw(body);
}