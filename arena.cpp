#include "arena.h"
#include "engine.h"
#include "apteczka.h"
#include "config.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Arena::Arena(GameEngine* gameEngine) {
    engine = gameEngine;
    currentState = ArenaState::Playing;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    p1HealthBg.setSize(sf::Vector2f(400.f, 30.f)); p1HealthBg.setFillColor(sf::Color::Red); p1HealthBg.setPosition(50.f, 50.f);
    p1HealthBar.setSize(sf::Vector2f(400.f, 30.f)); p1HealthBar.setFillColor(sf::Color::Green); p1HealthBar.setPosition(50.f, 50.f);
    p2HealthBg.setSize(sf::Vector2f(400.f, 30.f)); p2HealthBg.setFillColor(sf::Color::Red); p2HealthBg.setPosition(desktopMode.width - 450.f, 50.f);
    p2HealthBar.setSize(sf::Vector2f(400.f, 30.f)); p2HealthBar.setFillColor(sf::Color::Green); p2HealthBar.setPosition(desktopMode.width - 450.f, 50.f);

    if (!font.loadFromFile("Icons/arial.ttf")) {
        std::cout << "Brakuje czcionki arial.ttf w folderze Icons!" << std::endl;
    }
    overlayRect.setSize(sf::Vector2f(desktopMode.width, desktopMode.height));
    overlayRect.setFillColor(sf::Color(0, 0, 0, 220));

    winnerText.setFont(font); winnerText.setCharacterSize(100); winnerText.setFillColor(sf::Color::White);

    backButton.setSize(sf::Vector2f(400.f, 80.f)); backButton.setFillColor(sf::Color(100, 100, 100));
    backButton.setPosition(desktopMode.width / 2.f - 200.f, desktopMode.height / 2.f + 100.f);
    backButtonText.setFont(font); backButtonText.setString("Wroc do Menu"); backButtonText.setCharacterSize(40);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(backButton.getPosition().x + 65.f, backButton.getPosition().y + 15.f);

    srand(static_cast<unsigned int>(time(NULL)));
}

Arena::~Arena() {}

void Arena::init(int p1Map, int p2Map, int p1Id, int p2Id) {
    gameObjects.clear();

    int finalMapId = 10;
    if (p1Map == 12 && p2Map == 12) finalMapId = (rand() % 2 == 0) ? 10 : 11;
    else if (p1Map == 12) finalMapId = p2Map;
    else if (p2Map == 12) finalMapId = p1Map;
    else if (p1Map == p2Map) finalMapId = p1Map;
    else finalMapId = (rand() % 2 == 0) ? p1Map : p2Map;

    std::string mapPath = "Icons/char_" + std::to_string(finalMapId);
    if (!backgroundTexture.loadFromFile(mapPath + ".jpg")) backgroundTexture.loadFromFile(mapPath + ".png");

    backgroundSprite.setTexture(backgroundTexture);
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    backgroundSprite.setScale(static_cast<float>(desktopMode.width) / backgroundTexture.getSize().x,
                              static_cast<float>(desktopMode.height) / backgroundTexture.getSize().y);

    // CZYSTE TWORZENIE GRACZY ZA POMOCĄ ID (BEZ PATO-ŚCIEŻEK!)
    p1 = new Player(p1Id, 400.f, GROUND_HEIGHT, true);
    p2 = new Player(p2Id, 1400.f, GROUND_HEIGHT, false);

    gameObjects.push_back(std::unique_ptr<GameObject>(p1));
    gameObjects.push_back(std::unique_ptr<GameObject>(p2));

    currentState = ArenaState::Playing;
}

void Arena::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (currentState == ArenaState::Playing) {
        p1->handleInput();
        p2->handleInput();
    }
    else if (currentState == ArenaState::GameOver) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                engine->changeScreen(ScreenState::Menu);
            }
        }
    }
}

void Arena::update() {
    float dt = clock.restart().asSeconds();

    if (currentState == ArenaState::Playing) {
        if (rand() % APTECZKA_SPAWN_CHANCE == 0) gameObjects.push_back(std::make_unique<Apteczka>(static_cast<float>(rand() % 1800 + 50), GROUND_HEIGHT));

        for (auto& obj : gameObjects) obj->update(dt);

        if (p1->isCurrentlyAttacking() && p1->getBounds().intersects(p2->getBounds())) p2->takeDamage(ATTACK_DAMAGE);
        if (p2->isCurrentlyAttacking() && p2->getBounds().intersects(p1->getBounds())) p1->takeDamage(ATTACK_DAMAGE);

        for (auto& obj : gameObjects) {
            Apteczka* apteczka = dynamic_cast<Apteczka*>(obj.get());
            if (apteczka && apteczka->isActive()) {
                if (p1->getBounds().intersects(apteczka->getBounds())) { p1->heal(APTECZKA_HEAL_AMOUNT); apteczka->collect(); }
                else if (p2->getBounds().intersects(apteczka->getBounds())) { p2->heal(APTECZKA_HEAL_AMOUNT); apteczka->collect(); }
            }
        }

        for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
            if (!(*it)->isActive()) it = gameObjects.erase(it);
            else ++it;
        }

        p1HealthBar.setSize(sf::Vector2f(400.f * (p1->getHp() / (float)MAX_PLAYER_HP), 30.f));
        p2HealthBar.setSize(sf::Vector2f(400.f * (p2->getHp() / (float)MAX_PLAYER_HP), 30.f));

        if (p1->getHp() <= 0 || p2->getHp() <= 0) {
            currentState = ArenaState::GameOver;
            winnerText.setString(p1->getHp() <= 0 ? "Wygrywa Player 2!" : "Wygrywa Player 1!");
            sf::FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            winnerText.setPosition(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f - 100.f);
        }
    }
}

void Arena::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (auto& obj : gameObjects) obj->draw(window);
    window.draw(p1HealthBg); window.draw(p1HealthBar);
    window.draw(p2HealthBg); window.draw(p2HealthBar);

    if (currentState == ArenaState::GameOver) {
        window.draw(overlayRect); window.draw(winnerText);
        window.draw(backButton); window.draw(backButtonText);
    }
}