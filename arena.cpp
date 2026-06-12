#include "arena.h"
#include "engine.h"
#include <iostream>

Arena::Arena(GameEngine* gameEngine) {
    engine = gameEngine;

    
    if (!backgroundTexture.loadFromFile("Icons/widen_1840x0.jpg")) {
        std::cout << "Blad tla areny!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float scaleX = static_cast<float>(desktopMode.width) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(desktopMode.height) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    player1 = new Player("Animacje_Stojace.png", 400.f, 880.f, true);
    player2 = new Player("Animacje_Stojace.png", 1400.f, 880.f, false);
}
Arena::~Arena() {
    delete player1;
    delete player2;
}

void Arena::handleInput(sf::Event& event, sf::RenderWindow& window) {
    player1->handleInput();
    player2->handleInput();
}

void Arena::update() {
    float dt = clock.restart().asSeconds();

    player1->update(dt);
    player2->update(dt);

    if (player1->isCurrentlyAttacking() && player1->getHitbox().getGlobalBounds().intersects(player2->getHitbox().getGlobalBounds())) {
        std::cout << "P1 uderzyl P2!" << std::endl;
        player2->takeDamage(1); 
    }

    if (player2->isCurrentlyAttacking() && player2->getHitbox().getGlobalBounds().intersects(player1->getHitbox().getGlobalBounds())) {
        std::cout << "P2 uderzyl P1!" << std::endl;
        player1->takeDamage(1);
    }
}

void Arena::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    player1->draw(window);
    player2->draw(window);
}