#include "characterSelect.h"
#include "engine.h"
#include <iostream>

using Position = sf::Vector2f;

CharacterSelect::CharacterSelect(GameEngine* gameEngine) {
    engine = gameEngine;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float screenWidth = desktopMode.width;
    float screenHeight = desktopMode.height;

    if (!backgroundTexture.loadFromFile("Icons/charSelectBack.png")) {
        std::cout << "Error: no char select background!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(screenWidth / backgroundTexture.getSize().x,
        screenHeight / backgroundTexture.getSize().y);

    backBtnTex.loadFromFile("Icons/backBtnTex.png");

    uiButtons.push_back(Button(sf::Vector2f(50.f, 50.f), 0.2f, backBtnTex,
        [this]() { engine->changeScreen(ScreenState::Menu); }));

    fightBtnTex.loadFromFile("Icons/fightBtnTex.png");

    uiButtons.push_back(Button(sf::Vector2(screenWidth / 2.0f - 200.f, screenHeight * 0.82f), 0.4f, fightBtnTex,
        [this]() { engine->changeScreen(ScreenState::Arena); }));

    redFrameTex.loadFromFile("Icons/redFrame.png");
    violetFrameTex.loadFromFile("Icons/violetFrame.png");

    charIconTex.loadFromFile("Icons/charBtnTex.png");

    std::vector<CharIconData> leftIcons = {
        { Position(90.0, 200.0),  10, 0.60f, 0.45f, &redFrameTex },
        { Position(360.0, 200.0), 11, 0.60f, 0.45f, &redFrameTex },
        { Position(630.0, 200.0), 12, 0.60f, 0.45f, &redFrameTex },

        { Position(170.0, 520.0), 1, 0.45f, 0.45f, &redFrameTex },
        { Position(385.0, 520.0), 2, 0.45f, 0.45f, &redFrameTex },
        { Position(600.0, 520.0), 3, 0.45f, 0.45f, &redFrameTex }
    };

    iconSet(leftIcons, leftCharButtons);

    std::vector<CharIconData> rightIcons = {
        { Position(1090.0, 200.0), 13, 0.60f, 0.45f, &violetFrameTex },
        { Position(1360.0, 200.0), 14, 0.60f, 0.45f, &violetFrameTex },
        { Position(1630.0, 200.0), 15, 0.60f, 0.45f, &violetFrameTex },

        { Position(1170.0, 520.0), 4, 0.45f, 0.45f, &violetFrameTex },
        { Position(1385.0, 520.0), 5, 0.45f, 0.45f, &violetFrameTex },
        { Position(1600.0, 520.0), 6, 0.45f, 0.45f, &violetFrameTex }
    };

    iconSet(rightIcons, rightCharButtons);
}

void CharacterSelect::iconSet(const std::vector<CharIconData> &iconsVec, std::vector<Button> &buttonsVec) {
    for (size_t i = 0; i < iconsVec.size(); ++i) {
        const auto& icon = iconsVec[i];

        buttonsVec.push_back(Button(icon.position, icon.scaleX, icon.scaleY, charIconTex, [this, &buttonsVec, i]() {
            for (auto& btn : buttonsVec) {
                btn.setSelected(false);
            }
            buttonsVec[i].setSelected(true);
            std::cout << "Character " << i << " selected!" << std::endl;
        }));

        buttonsVec.back().setHoverTexture(*icon.frameTex);
    }
}

void CharacterSelect::handleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& button : uiButtons) {
        button.handleEvent(event, window);
    }
    for (auto& button : leftCharButtons) {
        button.handleEvent(event, window);
    }
    for (auto& button : rightCharButtons) {
        button.handleEvent(event, window);
    }
}

void CharacterSelect::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& button : uiButtons) {
        button.draw(window);
    }
    for (auto& button : leftCharButtons) {
        button.draw(window);
    }
    for (auto& button : rightCharButtons) {
        button.draw(window);
    }
}