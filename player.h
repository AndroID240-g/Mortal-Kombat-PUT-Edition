#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

// Stany, w jakich mo¿e znajdowaæ siê postaæ
enum class AnimState { Idle, Walk, Attack };

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape hitbox;

    
    int frameWidth;
    int frameHeight;
    int currentFrame;
    float animationTimer;
    float animationSpeed;

    AnimState currentState;
    bool facingRight;

    
    float speed;
    int hp;
    bool isPlayerOne;
    bool isAttacking;

public:
    Player(std::string texturePath, float startX, float startY, bool isP1);

    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Funkcje pomocnicze dla Areny
    sf::RectangleShape getHitbox() { return hitbox; }
    bool isCurrentlyAttacking() { return isAttacking; }
    void takeDamage(int damage);
    int getHp() { return hp; }
};

#endif