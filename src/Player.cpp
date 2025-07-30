#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/Animation.h"
#include "../include/Player.h"

Player::Player(sf::Vector2f h_size, sf::Vector2f t_size, sf::Texture* txtr, sf::Vector2u imgCount, float switchTime, float speed, float jumpHeight) : anim(txtr, imgCount, switchTime), collision(hitbox) {
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->h_size = h_size;
    this->t_size = t_size;

    row = 0;
    faceRight = true;
    showHitbox = false;

    hitbox.setSize(h_size);
    hitbox.setOrigin(hitbox.getSize() / 2.0f);
    hitbox.setPosition(sf::Vector2f(0.0f, 300.0f));

    if (showHitbox) {
        hitbox.setFillColor(sf::Color::Red);
    }
    else {
        hitbox.setFillColor(sf::Color::Transparent);
    }

    body.setSize(t_size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(txtr);
}

Player::~Player() {}

void Player::update(float deltaTime) {
    velocity.x *= 0.5f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
        canJump = false;

        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }

    velocity.y += 981.0f * deltaTime;
    //canJump = false;

    if (velocity.x == 0.0f) {
        row = 1;
    }
    else {
        row = 3;

        if (velocity.x) {
            if (velocity.x > 0)
                faceRight = true;
            else
                faceRight = false;
        }
    }

    anim.update(row, deltaTime, faceRight);
    body.setTextureRect(anim.uvRect);
    hitbox.move(velocity * deltaTime);
    body.setPosition(hitbox.getPosition());
}

void Player::draw(sf::RenderWindow& win) {
    win.draw(hitbox);
    win.draw(body);
}

void Player::onCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        // Collision on the left
        velocity.x = 0.0f;
    }
    else if (direction.x > 0.0f) {
        // Collision on the right
        velocity.x = 0.0f;
    }

    if (direction.y < 0.0f) {
        // Collision on the bottom
        velocity.y = 0.0f;
        canJump = true;

    }
    else if (direction.y > 0.0f) {
        // Collision on the top
        velocity.y -= 1.0f;
        //canJump = true;
    }
    printf("Colide! \n");
}
