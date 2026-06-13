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

    uiButtons.push_back(Button(sf::Vector2f(screenWidth / 2.0f - 200.f, screenHeight * 0.82f), 0.4f, fightBtnTex,
        [this]() { engine->changeScreen(ScreenState::Arena); }));

    redFrameTex.loadFromFile("Icons/redFrame.png");
    violetFrameTex.loadFromFile("Icons/violetFrame.png");

    charIconTex.loadFromFile("Icons/charBtnTex.png");

    std::vector<CharIconData> leftTopIcons = {
        { Position(90.0, 200.0),  10, 0.50f, 0.45f, &redFrameTex },
        { Position(360.0, 200.0), 11, 0.50f, 0.45f, &redFrameTex },
        { Position(630.0, 200.0), 12, 0.50f, 0.45f, &redFrameTex }
    };
    iconSet(leftTopIcons, leftTopCharButtons);

    std::vector<CharIconData> leftMedIcons = {
        { Position(170.0, 520.0), 1, 0.45f, 0.45f, &redFrameTex },
        { Position(385.0, 520.0), 2, 0.45f, 0.45f, &redFrameTex },
        { Position(600.0, 520.0), 3, 0.45f, 0.45f, &redFrameTex }
    };
    iconSet(leftMedIcons, leftMedCharButtons);

    std::vector<CharIconData> rightTopIcons = {
        { Position(1090.0, 200.0), 12, 0.50f, 0.45f, &violetFrameTex },
        { Position(1360.0, 200.0), 11, 0.50f, 0.45f, &violetFrameTex },
        { Position(1630.0, 200.0), 10, 0.50f, 0.45f, &violetFrameTex }
    };
    iconSet(rightTopIcons, rightTopCharButtons);

    std::vector<CharIconData> rightMedIcons = {
        { Position(1170.0, 520.0), 3, 0.45f, 0.45f, &violetFrameTex },
        { Position(1385.0, 520.0), 2, 0.45f, 0.45f, &violetFrameTex },
        { Position(1600.0, 520.0), 1, 0.45f, 0.45f, &violetFrameTex }
    };
    iconSet(rightMedIcons, rightMedCharButtons);

    // Automatyczne zaznaczenie domyślnych ikon
    if (!leftTopCharButtons.empty()) { leftTopCharButtons[0].setSelected(true); engine->setP1Map(10); }
    if (!rightTopCharButtons.empty()) { rightTopCharButtons[2].setSelected(true); engine->setP2Map(10); }
    if (!leftMedCharButtons.empty()) { leftMedCharButtons[0].setSelected(true); engine->setP1Char(1); }
    if (rightMedCharButtons.size() > 1) { rightMedCharButtons[1].setSelected(true); engine->setP2Char(2); }
}

void CharacterSelect::iconSet(const std::vector<CharIconData>& iconsVec, std::vector<Button>& buttonsVec) {
    for (size_t i = 0; i < iconsVec.size(); ++i) {
        const auto& icon = iconsVec[i];

        if (characterTextures.find(icon.charId) == characterTextures.end()) {
            sf::Texture tex;
            std::string path = "Icons/char_" + std::to_string(icon.charId);
            if (!tex.loadFromFile(path + ".png")) {
                tex.loadFromFile(path + ".jpg");
            }
            characterTextures[icon.charId] = tex;
        }

        buttonsVec.push_back(Button(icon.position, icon.scaleX, icon.scaleY, characterTextures[icon.charId], [this, &buttonsVec, i, icon]() {
            for (auto& btn : buttonsVec) btn.setSelected(false);
            buttonsVec[i].setSelected(true);

            if (icon.charId >= 10) {
                if (icon.frameTex == &redFrameTex) engine->setP1Map(icon.charId);
                else engine->setP2Map(icon.charId);
            }
            else {
                if (icon.frameTex == &redFrameTex) engine->setP1Char(icon.charId);
                else engine->setP2Char(icon.charId);
            }
            std::cout << "Wybrano ID: " << icon.charId << std::endl;
            }));
        buttonsVec.back().setHoverTexture(*icon.frameTex);
    }
}

void CharacterSelect::handleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& button : uiButtons) button.handleEvent(event, window);
    for (auto& button : leftTopCharButtons) button.handleEvent(event, window);
    for (auto& button : rightTopCharButtons) button.handleEvent(event, window);
    for (auto& button : leftMedCharButtons) button.handleEvent(event, window);
    for (auto& button : rightMedCharButtons) button.handleEvent(event, window);
}

void CharacterSelect::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (auto& button : uiButtons) button.draw(window);
    for (auto& button : leftTopCharButtons) button.draw(window);
    for (auto& button : rightTopCharButtons) button.draw(window);
    for (auto& button : leftMedCharButtons) button.draw(window);
    for (auto& button : rightMedCharButtons) button.draw(window);
}