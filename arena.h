#ifndef ARENA_H
#define ARENA_H

#include <SFML/Graphics.hpp>
#include "player.h"

class GameEngine;

class Arena {
private:
    GameEngine* engine;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Player* player1;
    Player* player2;

    sf::Clock clock;

public:
    Arena(GameEngine* gameEngine);
    ~Arena();

    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);
};

#endif