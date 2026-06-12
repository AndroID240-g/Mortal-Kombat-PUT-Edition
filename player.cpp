#include "player.h"

Player::Player(std::string texturePath, float startX, float startY, bool isP1)
    : anim(texturePath, 64, 64) // UWAGA: Jeśli klatki są poucinane, trzeba zmienić to 64, 64 na rzeczywisty rozmiar jednej klatki z obrazka!
{
    isPlayerOne = isP1;
    speed = PLAYER_SPEED;
    hp = MAX_PLAYER_HP;
    velocityX = 0.f;
    velocityY = 0.f;
    isJumping = false;

    currentState = AnimState::Idle;
    facingRight = isP1;
    isAttacking = false;

    anim.setPosition(startX, GROUND_HEIGHT);
    anim.setScale(facingRight ? 4.f : -4.f, 4.f);

    hitbox.setSize(sf::Vector2f(128.f, 192.f));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(2.f);
}

void Player::handleInput() {
    if (currentState == AnimState::Attack) return;

    currentState = AnimState::Idle;
    isAttacking = false;
    velocityX = 0.f;

    if (isPlayerOne) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocityX = -speed;
            currentState = AnimState::Walk;
            facingRight = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocityX = speed;
            currentState = AnimState::Walk;
            facingRight = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) {
            velocityY = JUMP_VELOCITY;
            isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            currentState = AnimState::Attack;
            isAttacking = true;
            velocityX = 0.f;
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocityX = -speed;
            currentState = AnimState::Walk;
            facingRight = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocityX = speed;
            currentState = AnimState::Walk;
            facingRight = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
            velocityY = JUMP_VELOCITY;
            isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            currentState = AnimState::Attack;
            isAttacking = true;
            velocityX = 0.f;
        }
    }
}

void Player::update(float deltaTime) {
    velocityY += GRAVITY * deltaTime;

    anim.move(velocityX * deltaTime, velocityY * deltaTime);

    if (anim.getPosition().y >= GROUND_HEIGHT) {
        anim.setPosition(anim.getPosition().x, GROUND_HEIGHT);
        velocityY = 0.f;
        isJumping = false;
    }

    // --- ZMIANY ANIMACJI SĄ TUTAJ ---
    if (currentState == AnimState::Idle) {
        anim.setAnimation(0, 7); // Rząd 1 (indeks 0), 7 klatek
    }
    else if (currentState == AnimState::Walk) {
        anim.setAnimation(1, 9); // Rząd 2 (indeks 1), 9 klatek
    }
    else if (currentState == AnimState::Attack) {
        anim.setAnimation(5, 6); // Rząd 6 (indeks 5), 6 klatek
    }

    bool animationFinished = anim.update(deltaTime);

    if (currentState == AnimState::Attack && animationFinished) {
        currentState = AnimState::Idle;
        isAttacking = false;
    }

    if (facingRight) {
        anim.setScale(4.f, 4.f);
    }
    else {
        anim.setScale(-4.f, 4.f);
    }

    hitbox.setPosition(anim.getPosition().x - hitbox.getSize().x / 2.f, anim.getPosition().y - hitbox.getSize().y / 2.f);
}

void Player::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

void Player::heal(int amount) {
    hp += amount;
    if (hp > MAX_PLAYER_HP) hp = MAX_PLAYER_HP;
}

void Player::draw(sf::RenderWindow& window) {
    anim.draw(window);
}