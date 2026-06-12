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

    int player1CharId = -1; // -1 means no selection yet
    int player2CharId = -1;

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

    void setPlayer1CharId(int id) { player1CharId = id; }
    void setPlayer2CharId(int id) { player2CharId = id; }

    int getPlayer1CharId() const { return player1CharId; }
    int getPlayer2CharId() const { return player2CharId; }
};

#endif