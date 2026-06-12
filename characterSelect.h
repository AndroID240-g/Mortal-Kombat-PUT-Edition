#ifndef CHARACTERSELECT_H
#define CHARACTERSELECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "buttons.h"

class GameEngine;

class CharacterSelect {
private:
    GameEngine* engine;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture backBtnTex;

    sf::Texture charIconTex;
    sf::Texture fightBtnTex;

    std::vector<Button> selectButtons;

public:
    CharacterSelect(GameEngine* gameEngine);

    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif
