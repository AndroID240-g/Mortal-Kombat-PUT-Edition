#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "buttons.h"

class GameEngine;

class MainMenu {
private:
    GameEngine* engine;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture startBtnTex;
    sf::Texture quitBtnTex;
    sf::Texture settingsBtnTex;

    std::vector<Button> menuButtons;

public:
    MainMenu(GameEngine* gameEngine);

    void handleInput(sf::Event& event, sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);
};

#endif