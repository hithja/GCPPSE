#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Animation.h"
#include "../include/Collision.h"

class Player {
private:
    sf::RectangleShape body;
    sf::RectangleShape hitbox;

    Animation anim;
    unsigned int row;
    float speed;
    bool faceRight;
    bool showHitbox;

    Collision collision;
    sf::Vector2f velocity;
    float jumpHeight;
    
    sf::Vector2f t_size;
    sf::Vector2f h_size;
    
public:
    Player(sf::Vector2f h_size, sf::Vector2f t_size, sf::Texture* txtr, sf::Vector2u imgCount, float switchTime, float speed, float jumpHeight);
    ~Player();

    bool canJump;
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& win);
    void onCollision(sf::Vector2f direction);

    sf::Vector2f getPos() { return hitbox.getPosition(); }
    Collision& getCollider() { return collision; }
};
