#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>


enum class ScreenState { Menu, Settings, CharacterSelect, Arena };


class MainMenu;
class SettingsWindow;
class CharacterSelect;
class Arena;

class GameEngine {
private:
    sf::RenderWindow window;
    ScreenState currentScreen;

    MainMenu* mainMenu;
    SettingsWindow* settingsWindow;
    CharacterSelect* characterSelect;
    Arena* arena;

    void processEvents();
    void update();
    void render();

public:
    GameEngine();
    ~GameEngine();

    void run();


    void changeScreen(ScreenState newState);
};

#endif