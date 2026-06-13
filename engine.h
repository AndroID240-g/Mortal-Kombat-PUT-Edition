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

    int selectedP1MapId = 10;
    int selectedP2MapId = 11;
    int selectedP1Id = 1;
    int selectedP2Id = 2;

    void processEvents();
    void update();
    void render();

public:
    GameEngine();
    ~GameEngine();

    void run();
    void changeScreen(ScreenState newState);

    void setP1Map(int id) { selectedP1MapId = id; }
    void setP2Map(int id) { selectedP2MapId = id; }
    void setP1Char(int id) { selectedP1Id = id; }
    void setP2Char(int id) { selectedP2Id = id; }
};

#endif