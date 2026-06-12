#include "mainMenu.h"
#include "engine.h"
#include <iostream>

MainMenu::MainMenu(GameEngine* gameEngine) {
    engine = gameEngine;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float screenWidth = desktopMode.width;
    float screenHeight = desktopMode.height;

    if (!backgroundTexture.loadFromFile("Icons/mainWindowBack.png")) {
        std::cout << "Error: no background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(screenWidth / backgroundTexture.getSize().x, screenHeight / backgroundTexture.getSize().y);

    startBtnTex.loadFromFile("Icons/startBtnTex.png");
    quitBtnTex.loadFromFile("Icons/quitBtnTex.png");
    settingsBtnTex.loadFromFile("Icons/settingsBtnTex.png");


    menuButtons.push_back(Button(
        sf::Vector2f(screenWidth / 2.0f - 280.f, 550.f), 0.5f, startBtnTex,
        [this]() { engine->changeScreen(ScreenState::CharacterSelect); }));

    menuButtons.push_back(Button(
        sf::Vector2f(screenWidth / 2.0f - 260.f, 732.f), 0.5f, settingsBtnTex,
        [this]() { engine->changeScreen(ScreenState::Settings); }));

    menuButtons.push_back(Button(
        sf::Vector2f(screenWidth / 2.0f - 245.f, 900.f), 0.5f, quitBtnTex,
        []() { exit(0); }));
}

void MainMenu::handleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& button : menuButtons) {
        button.handleEvent(event, window);
    }
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& button : menuButtons) {
        button.draw(window);
    }
}