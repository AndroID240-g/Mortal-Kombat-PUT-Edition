#ifndef ARENA_H
#define ARENA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "gameobject.h"
#include "player.h"

class GameEngine;

class Arena {
private:
    GameEngine* engine;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::vector<std::unique_ptr<GameObject>> gameObjects;
    Player* p1;
    Player* p2;

    sf::RectangleShape p1HealthBg;
    sf::RectangleShape p1HealthBar;
    sf::RectangleShape p2HealthBg;
    sf::RectangleShape p2HealthBar;

    sf::Clock clock;

public:
    Arena(GameEngine* gameEngine);
    ~Arena();

    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);
    void init();
};

#endif