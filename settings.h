#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "buttons.h"

class GameEngine;

class SettingsWindow {
private:
    GameEngine* engine;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture backBtnTex;

    std::vector<Button> settingsButtons;

public:
    SettingsWindow(GameEngine* gameEngine);

    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif