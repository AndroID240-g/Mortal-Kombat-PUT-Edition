#include "characterSelect.h"
#include "engine.h"
#include <iostream>
#include <vector>

struct IconPos {
    float x;
    float y;
    int charId;
};

CharacterSelect::CharacterSelect(GameEngine* gameEngine) {
    engine = gameEngine;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float screenWidth = desktopMode.width;
    float screenHeight = desktopMode.height;

    if (!backgroundTexture.loadFromFile("charSelectBack.png")) {
        std::cout << "Error: no char select background!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(screenWidth / backgroundTexture.getSize().x, screenHeight / backgroundTexture.getSize().y);

    backBtnTex.loadFromFile("backBtnTex.png");

    selectButtons.push_back(Button(sf::Vector2f(50.f, 50.f), 0.2f, backBtnTex,
                                   [this]() { engine->changeScreen(ScreenState::Menu); }));

    charIconTex.loadFromFile("charBtnTex.png");

    std::vector<IconPos> characterPositions = {
        { screenWidth * 0.05f, screenHeight * 0.15f, 0 },
        { screenWidth * 0.18f, screenHeight * 0.15f, 1 },
        { screenWidth * 0.31f, screenHeight * 0.15f, 2 },
        { screenWidth * 0.45f, screenHeight * 0.18f, 100 },
        { screenWidth * 0.58f, screenHeight * 0.15f, 3 },
        { screenWidth * 0.71f, screenHeight * 0.15f, 4 },
        { screenWidth * 0.84f, screenHeight * 0.15f, 5 },

        { screenWidth * 0.10f, screenHeight * 0.50f, 6 },
        { screenWidth * 0.22f, screenHeight * 0.40f, 7 },
        { screenWidth * 0.22f, screenHeight * 0.60f, 8 },
        { screenWidth * 0.34f, screenHeight * 0.50f, 101 },

        { screenWidth * 0.62f, screenHeight * 0.50f, 102 },
        { screenWidth * 0.74f, screenHeight * 0.40f, 9 },
        { screenWidth * 0.74f, screenHeight * 0.60f, 10 },
        { screenWidth * 0.86f, screenHeight * 0.50f, 11 }
    };

    for (const auto& icon : characterPositions) {
        int id = icon.charId;
        selectButtons.push_back(Button(sf::Vector2f(icon.x, icon.y), 0.3f, charIconTex,
            [id]() { std::cout << "ID: " << id << std::endl; }));
    }

    fightBtnTex.loadFromFile("fightBtnTex.png");

    selectButtons.push_back(Button(sf::Vector2f(screenWidth / 2.0f - 200.f, screenHeight * 0.82f), 0.4f, fightBtnTex,
        [this]() { engine->changeScreen(ScreenState::Arena); }));

}
void CharacterSelect::handleInput(sf::Event& event, sf::RenderWindow& window) {
    for (auto& button : selectButtons) {
        button.handleEvent(event, window);
    }
}

void CharacterSelect::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (auto& button : selectButtons) {
        button.draw(window);
    }
}