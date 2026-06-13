#include "engine.h"
#include "mainMenu.h"
#include "settings.h"
#include "characterSelect.h"
#include "arena.h"

GameEngine::GameEngine() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(desktop, "Mortal Kombad: PUT Edition", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    currentScreen = ScreenState::Menu;

    mainMenu = new MainMenu(this);
    settingsWindow = new SettingsWindow(this);
    characterSelect = new CharacterSelect(this);
    arena = new Arena(this);
}

GameEngine::~GameEngine() {
    delete mainMenu;
    delete settingsWindow;
    delete characterSelect;
    delete arena;
}

void GameEngine::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameEngine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (currentScreen == ScreenState::Menu) mainMenu->handleInput(event, window);
        else if (currentScreen == ScreenState::Settings) settingsWindow->handleInput(event, window);
        else if (currentScreen == ScreenState::CharacterSelect) characterSelect->handleInput(event, window);
        else if (currentScreen == ScreenState::Arena) arena->handleInput(event, window);
    }
}

void GameEngine::update() {
    if (currentScreen == ScreenState::Arena) {
        arena->update();
    }
}

void GameEngine::render() {
    window.clear();
    if (currentScreen == ScreenState::Menu) mainMenu->draw(window);
    else if (currentScreen == ScreenState::Settings) settingsWindow->draw(window);
    else if (currentScreen == ScreenState::CharacterSelect) characterSelect->draw(window);
    else if (currentScreen == ScreenState::Arena) arena->render(window);
    window.display();
}

void GameEngine::changeScreen(ScreenState newState) {
    if (newState == ScreenState::Arena) {
        arena->init(selectedP1MapId, selectedP2MapId, selectedP1Id, selectedP2Id);
    }
    currentScreen = newState;
}