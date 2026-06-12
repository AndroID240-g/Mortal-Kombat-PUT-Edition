#ifndef CHARACTERSELECT_H
#define CHARACTERSELECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "buttons.h"

class GameEngine;

struct CharIconData {
    sf::Vector2f position;
    int charId;
    float scaleX;
    float scaleY;
    const sf::Texture* frameTex;
};

class CharacterSelect {
public:
    CharacterSelect(GameEngine* gameEngine);
    ~CharacterSelect() = default;

    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void iconSet(const std::vector<CharIconData>& vec, std::vector<Button>& buttonsVec);

private:
    GameEngine* engine;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture backBtnTex;
    sf::Texture fightBtnTex;
    sf::Texture charIconTex;

    sf::Texture redFrameTex;
    sf::Texture violetFrameTex;

    std::vector<Button> uiButtons;
    std::vector<Button> leftCharButtons;
    std::vector<Button> rightCharButtons;
};

#endif