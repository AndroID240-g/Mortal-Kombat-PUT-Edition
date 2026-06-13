#ifndef ARENA_H
#define ARENA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "gameobject.h"
#include "player.h"

class GameEngine;

enum class ArenaState { Playing, GameOver };

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

    ArenaState currentState;
    sf::RectangleShape overlayRect;
    sf::Font font;
    sf::Text winnerText;
    sf::RectangleShape backButton;
    sf::Text backButtonText;

public:
    Arena(GameEngine* gameEngine);
    ~Arena();

    void init(int p1MapId, int p2MapId, int p1Id, int p2Id);

    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);
};

#endif