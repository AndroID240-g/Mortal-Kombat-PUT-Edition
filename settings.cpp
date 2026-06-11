#include "settings.h"
#include "engine.h"
#include <iostream>

SettingsWindow::SettingsWindow(GameEngine* gameEngine) {
    engine = gameEngine;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float screenWidth = desktopMode.width;
    float screenHeight = desktopMode.height;

    if (!backgroundTexture.loadFromFile("settingsBack.png")) {
        std::cout << "Error: no settings background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(screenWidth / backgroundTexture.getSize().x, screenHeight / backgroundTexture.getSize().y);

    if (!backBtnTex.loadFromFile("backBtnTex.png")) {
        std::cout << "Error: no back button image!" << std::endl;
    }

    settingsButtons.push_back(Button(
        sf::Vector2f(screenWidth / 2.0f - 380.f, 850.f), 0.5f, backBtnTex,
        [this]() { engine->changeScreen(ScreenState::Menu); }));
}

void SettingsWindow::handleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& button : settingsButtons) {
        button.handleEvent(event, window);
    }
}

void SettingsWindow::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& button : settingsButtons) {
        button.draw(window);
    }
}