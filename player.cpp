#include "player.h"
#include <iostream>

Player::Player(std::string texturePath, float startX, float startY, bool isP1) {
    isPlayerOne = isP1;
    speed = 300.f;
    hp = 100;

    currentState = AnimState::Idle;
    facingRight = isP1;
    isAttacking = false;

    
    sf::Image image;
    
    if (!image.loadFromFile(texturePath)) {
        std::cout << "Blad ladowania grafiki: " << texturePath << std::endl;
    }
    
    image.createMaskFromColor(sf::Color(255, 0, 255));

    
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setPosition(startX, startY);

    frameWidth = 384;
    frameHeight = 224;

    currentFrame = 0;
    animationTimer = 0.f;
    animationSpeed = 0.15f;

    sprite.setScale(4.f, 4.f);
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);

    hitbox.setSize(sf::Vector2f(frameWidth * 2.f, frameHeight * 3.f));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(2.f);
}

void Player::handleInput() {
    if (currentState == AnimState::Attack) return;

    currentState = AnimState::Idle;
    isAttacking = false;

    if (isPlayerOne) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite.move(-speed * 0.016f, 0);
            currentState = AnimState::Walk;
            facingRight = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move(speed * 0.016f, 0);
            currentState = AnimState::Walk;
            facingRight = true;
        }
        // Atak - Spacja dla P1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            currentState = AnimState::Attack;
            currentFrame = 0;
            isAttacking = true;
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-speed * 0.016f, 0);
            currentState = AnimState::Walk;
            facingRight = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(speed * 0.016f, 0);
            currentState = AnimState::Walk;
            facingRight = true;
        }
        // Atak - Enter dla P2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            currentState = AnimState::Attack;
            currentFrame = 0;
            isAttacking = true;
        }
    }
}

void Player::update(float deltaTime) {
    animationTimer += deltaTime;

    int row = 0;
    int maxFrames = 4;

    
    if (currentState == AnimState::Idle) {
        row = 0;
        maxFrames = 1; 
    }
    else if (currentState == AnimState::Walk) {
        row = 0; 
        maxFrames = 4;
    }
    else if (currentState == AnimState::Attack) {
        row = 1; 
        maxFrames = 4;
    }

    if (animationTimer >= animationSpeed) {
        currentFrame++;
        animationTimer = 0.f;

        if (currentState == AnimState::Attack && currentFrame >= maxFrames) {
            currentState = AnimState::Idle;
            isAttacking = false;
            currentFrame = 0;
        }
        else if (currentFrame >= maxFrames) {
            currentFrame = 0;
        }
    }

    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));

    if (facingRight) {
        sprite.setScale(4.f, 4.f);
    }
    else {
        sprite.setScale(-4.f, 4.f);
    }

    hitbox.setPosition(sprite.getPosition().x - hitbox.getSize().x / 2.f, sprite.getPosition().y - hitbox.getSize().y / 2.f);
}

void Player::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
   
}