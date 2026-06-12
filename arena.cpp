#include "arena.h"
#include "engine.h"
#include "apteczka.h"
#include "config.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Arena::Arena(GameEngine* gameEngine) {
    engine = gameEngine;

    if (!backgroundTexture.loadFromFile("Icons/widen_1840x0.jpg")) {
        std::cout << "Blad tla areny!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float scaleX = static_cast<float>(desktopMode.width) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(desktopMode.height) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // --- ZMIANA GRAFIKI TUTAJ ---
    p1 = new Player("Icons/Animacje_Stojace.jpg", 400.f, GROUND_HEIGHT, true);
    p2 = new Player("Icons/Animacje_Stojace.jpg", 1400.f, GROUND_HEIGHT, false);

    gameObjects.push_back(std::unique_ptr<GameObject>(p1));
    gameObjects.push_back(std::unique_ptr<GameObject>(p2));

    p1HealthBg.setSize(sf::Vector2f(400.f, 30.f));
    p1HealthBg.setFillColor(sf::Color::Red);
    p1HealthBg.setPosition(50.f, 50.f);

    p1HealthBar.setSize(sf::Vector2f(400.f, 30.f));
    p1HealthBar.setFillColor(sf::Color::Green);
    p1HealthBar.setPosition(50.f, 50.f);

    p2HealthBg.setSize(sf::Vector2f(400.f, 30.f));
    p2HealthBg.setFillColor(sf::Color::Red);
    p2HealthBg.setPosition(desktopMode.width - 450.f, 50.f);

    p2HealthBar.setSize(sf::Vector2f(400.f, 30.f));
    p2HealthBar.setFillColor(sf::Color::Green);
    p2HealthBar.setPosition(desktopMode.width - 450.f, 50.f);

    srand(static_cast<unsigned int>(time(NULL)));
}

Arena::~Arena() {
}

void Arena::handleInput(sf::Event& event, sf::RenderWindow& window) {
    p1->handleInput();
    p2->handleInput();
}

void Arena::update() {
    float dt = clock.restart().asSeconds();

    if (rand() % APTECZKA_SPAWN_CHANCE == 0) {
        float randomX = rand() % 1800 + 50;
        gameObjects.push_back(std::make_unique<Apteczka>(randomX, GROUND_HEIGHT));
    }

    for (auto& obj : gameObjects) {
        obj->update(dt);
    }

    if (p1->isCurrentlyAttacking() && p1->getBounds().intersects(p2->getBounds())) {
        p2->takeDamage(ATTACK_DAMAGE);
    }

    if (p2->isCurrentlyAttacking() && p2->getBounds().intersects(p1->getBounds())) {
        p1->takeDamage(ATTACK_DAMAGE);
    }

    for (auto& obj : gameObjects) {
        Apteczka* apteczka = dynamic_cast<Apteczka*>(obj.get());
        if (apteczka && apteczka->isActive()) {
            if (p1->getBounds().intersects(apteczka->getBounds())) {
                p1->heal(APTECZKA_HEAL_AMOUNT);
                apteczka->collect();
            }
            else if (p2->getBounds().intersects(apteczka->getBounds())) {
                p2->heal(APTECZKA_HEAL_AMOUNT);
                apteczka->collect();
            }
        }
    }

    for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
        if (!(*it)->isActive()) {
            it = gameObjects.erase(it);
        }
        else {
            ++it;
        }
    }

    p1HealthBar.setSize(sf::Vector2f(400.f * (p1->getHp() / (float)MAX_PLAYER_HP), 30.f));
    p2HealthBar.setSize(sf::Vector2f(400.f * (p2->getHp() / (float)MAX_PLAYER_HP), 30.f));
}

void Arena::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& obj : gameObjects) {
        obj->draw(window);
    }

    window.draw(p1HealthBg);
    window.draw(p1HealthBar);
    window.draw(p2HealthBg);
    window.draw(p2HealthBar);
}