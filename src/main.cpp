#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../include/Player.h"
#include "../include/Object.h"

static const float VIEW_HEIGHT = 512.0f;

void resizeView(const sf::RenderWindow& win, sf::View& view) {
    float aspectRatio = float(win.getSize().x) / float(win.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1908, 1080), "SFML Test", sf::Style::Close | sf::Style::Titlebar);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::Texture playerTxtr;
    playerTxtr.loadFromFile("./textures/goose2.png");
    sf::Texture appleTxtr;
    appleTxtr.loadFromFile("./textures/apple.png");

    Player player(sf::Vector2f(100.0f, 135.0f), sf::Vector2f(240.0f, 150.0f), &playerTxtr, sf::Vector2u(4, 4), 0.3f, 350.0f, 250.0f);

    std::vector<Object> platforms;
    platforms.push_back(Object(sf::Vector2f(1000.0f, 50.0f), sf::Vector2f(1000.0f, 50.0f), sf::Vector2f(0.0f, 400.0f), nullptr, false));
    platforms.push_back(Object(sf::Vector2f(500.0f, 50.0f), sf::Vector2f(500.0f, 50.0f), sf::Vector2f(850.0f, 200.0f), nullptr, false));

    float deltaTime = 0.0f;
    sf::Clock clock;

    // Game Loop
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;

        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    resizeView(window, view);
                    break;
                default:
                    break;
            }
        }

        player.update(deltaTime);

        sf::Vector2f direction;
        
        for (Object& platform : platforms)
            if (platform.getCollider().checkCollision(player.getCollider(), direction, 1.0f)) {
                player.onCollision(direction);
                platform.getCollider().checkCollision(player.getCollider(), direction, 1.0f);
            }
                

        view.setCenter(player.getPos());

        // Update screen
        window.clear(sf::Color::Blue);
        window.setView(view);

        player.draw(window);

        for (Object& platform : platforms)
            platform.draw(window);

        window.display();
    }
    
    return 0;
}