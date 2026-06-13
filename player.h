#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "gameobject.h"
#include "animation.h"
#include "config.h"

enum class AnimState { Idle, Walk, Attack };

class Player : public GameObject {
private:
    Animation anim;
    sf::RectangleShape hitbox;

    AnimState currentState;
    bool facingRight;
    float speed;
    float velocityX;
    float velocityY;
    bool isJumping;
    int hp;
    bool isPlayerOne;
    bool isAttacking;
    float invincibilityTimer;

    // --- JEDYNA NOWA ZMIENNA ---
    // Zapisujemy kim gramy, żeby wiedzieć jak rysować animacje
    int myCharId;

public:
    Player(int charId, float startX, float startY, bool isP1);

    void setPosition(float x, float y);
    void handleInput();
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() override { return hitbox.getGlobalBounds(); }

    void takeDamage(int damage);
    void heal(int amount);
    int getHp() { return hp; }
    bool isCurrentlyAttacking() { return isAttacking; }
};

#endif