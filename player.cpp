#include "player.h"

static const float GROUND_OFFSET = 30.f; // OK - postac stoi dobrze, nie zmieniaj

// --- DO DOSTROJENIA WIZUALNEGO ---
// Jesli przy chodzeniu postac SKACZE W GORE -> ZWIEKSZ WALK_Y_OFFSET (np. 10, 20, 30...)
// Jesli przy chodzeniu postac WPADA W DOL    -> ZMNIEJSZ (wartosci ujemne)
// Analogicznie dla ATTACK_Y_OFFSET, jesli atak rowniez "skacze"
static const float WALK_Y_OFFSET = 0.f;
static const float ATTACK_Y_OFFSET = 0.f;

// --- ROZMIAR HITBOXA - DO DOSTROJENIA ---
// Czerwona ramka powinna obejmowac postac. Zmieniaj te 2 liczby az bedzie pasowac.
static const float HITBOX_WIDTH = 120.f;
static const float HITBOX_HEIGHT = 220.f;

Player::Player(std::string texturePath, float startX, float startY, bool isP1)
    : anim(texturePath, 385, 280)
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

    anim.setPosition(startX, GROUND_HEIGHT + GROUND_OFFSET);
    anim.setScale(facingRight ? 4.f : -4.f, 4.f);

    hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
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

    float groundLevel = GROUND_HEIGHT + GROUND_OFFSET;
    if (anim.getPosition().y >= groundLevel) {
        anim.setPosition(anim.getPosition().x, groundLevel);
        velocityY = 0.f;
        isJumping = false;
    }

    // --- BLOKADA WYJSCIA POZA ARENE ---
    {
        float screenWidth = static_cast<float>(sf::VideoMode::getDesktopMode().width);
        float halfWidth = HITBOX_WIDTH / 2.f;
        sf::Vector2f pos = anim.getPosition();

        if (pos.x - halfWidth < 0.f) {
            pos.x = halfWidth;
            anim.setPosition(pos.x, pos.y);
        }
        else if (pos.x + halfWidth > screenWidth) {
            pos.x = screenWidth - halfWidth;
            anim.setPosition(pos.x, pos.y);
        }
    }

    // --- ZMIANY ANIMACJI SĄ TUTAJ ---
    if (currentState == AnimState::Idle) {
        anim.setAnimation(0, 7, 0.f);
    }
    else if (currentState == AnimState::Walk) {
        anim.setAnimation(1, 9, WALK_Y_OFFSET);
    }
    else if (currentState == AnimState::Attack) {
        anim.setAnimation(5, 6, ATTACK_Y_OFFSET);
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

    // Hitbox: staly rozmiar, wycentrowany na pozycji postaci
    sf::Vector2f pos = anim.getPosition();
    hitbox.setPosition(pos.x - HITBOX_WIDTH / 2.f, pos.y - HITBOX_HEIGHT / 2.f);
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