#include "player.h"

static const float GROUND_OFFSET = 30.f;

// --- PROSTE FUNKCJE POMOCNICZE DLA KONSTRUKTORA ---
// Dzięki temu nie musimy pisać skomplikowanych struktur.
std::string getTexPath(int id) { return (id == 1) ? "Icons/char_2_fight.png" : "Icons/char_1_fight.png"; }
int getFrameW(int id) { return (id == 1) ? 64 : 385; }
int getFrameH(int id) { return (id == 1) ? 64 : 280; }
bool getUseMask(int id) { return (id == 1) ? true : false; }
sf::Color getMaskColor(int id) { return (id == 1) ? sf::Color(255, 0, 255) : sf::Color::Black; }


Player::Player(int charId, float startX, float startY, bool isP1)
    : anim(getTexPath(charId), getFrameW(charId), getFrameH(charId), getUseMask(charId), getMaskColor(charId))
{
    myCharId = charId; // Zapamiętujemy kim jesteśmy

    isPlayerOne = isP1;
    speed = PLAYER_SPEED;
    hp = MAX_PLAYER_HP;
    velocityX = 0.f; velocityY = 0.f;
    isJumping = false;
    invincibilityTimer = 0.f;
    currentState = AnimState::Idle;
    facingRight = isP1;
    isAttacking = false;

    anim.setPosition(startX, GROUND_HEIGHT + GROUND_OFFSET);
    anim.setScale(facingRight ? 4.f : -4.f, 4.f);

    // --- PROSTE USTAWIENIE HITBOXÓW ---
    if (myCharId == 1) {
        hitbox.setSize(sf::Vector2f(120.f, 200.f)); // Hitbox Ninjy
    }
    else {
        hitbox.setSize(sf::Vector2f(400.f, 220.f)); // Hitbox Jojo
    }

    hitbox.setFillColor(sf::Color::Transparent);
    // Odznacz komentarz poniżej jeśli chcesz widzieć ramki kolizji
    // hitbox.setOutlineColor(sf::Color::Red);
    // hitbox.setOutlineThickness(2.f);
}

void Player::setPosition(float x, float y) { anim.setPosition(x, y); }

void Player::handleInput() {
    if (currentState == AnimState::Attack) return;
    currentState = AnimState::Idle;
    isAttacking = false;
    velocityX = 0.f;

    if (isPlayerOne) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { velocityX = -speed; currentState = AnimState::Walk; facingRight = false; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { velocityX = speed; currentState = AnimState::Walk; facingRight = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping) { velocityY = JUMP_VELOCITY; isJumping = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { currentState = AnimState::Attack; isAttacking = true; velocityX = 0.f; }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { velocityX = -speed; currentState = AnimState::Walk; facingRight = false; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { velocityX = speed; currentState = AnimState::Walk; facingRight = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) { velocityY = JUMP_VELOCITY; isJumping = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { currentState = AnimState::Attack; isAttacking = true; velocityX = 0.f; }
    }
}

void Player::update(float deltaTime) {
    velocityY += GRAVITY * deltaTime;
    anim.move(velocityX * deltaTime, velocityY * deltaTime);

    if (invincibilityTimer > 0.f) invincibilityTimer -= deltaTime;

    float groundLevel = GROUND_HEIGHT + GROUND_OFFSET;
    if (anim.getPosition().y >= groundLevel) {
        anim.setPosition(anim.getPosition().x, groundLevel);
        velocityY = 0.f; isJumping = false;
    }

    float screenWidth = static_cast<float>(sf::VideoMode::getDesktopMode().width);
    float halfWidth = hitbox.getSize().x / 2.f;
    sf::Vector2f pos = anim.getPosition();
    if (pos.x - halfWidth < 0.f) anim.setPosition(halfWidth, pos.y);
    else if (pos.x + halfWidth > screenWidth) anim.setPosition(screenWidth - halfWidth, pos.y);

    // =========================================================
    // --- BARDZO PROSTA I CZYTELNA LOGIKA ANIMACJI ---
    // =========================================================

    if (myCharId == 1) {
        // ------------------
        // ZIELONY NINJA
        // ------------------
        if (currentState == AnimState::Idle) {
            anim.setAnimation(0, 1, 0.f);
            anim.setSpeed(0.15f);
        }
        else if (currentState == AnimState::Walk) {
            anim.setAnimation(0, 6, 0.f);
            anim.setSpeed(0.12f);
        }
        else if (currentState == AnimState::Attack) {
            anim.setAnimation(1, 6, 0.f);
            anim.setSpeed(0.06f);
        }
    }
    else {
        // ------------------
        // JOJO (Każde inne ID)
        // ------------------
        if (currentState == AnimState::Idle) {
            anim.setAnimation(0, 7, 0.f);
            anim.setSpeed(0.15f);
        }
        else if (currentState == AnimState::Walk) {
            anim.setAnimation(1, 9, -60.f); // Tu masz swój offset ściągający w dół!
            anim.setSpeed(0.12f);
        }
        else if (currentState == AnimState::Attack) {
            anim.setAnimation(5, 6, -60.f); // Offset dla ataku
            anim.setSpeed(0.06f);
        }
    }

    // =========================================================

    bool animationFinished = anim.update(deltaTime);

    if (currentState == AnimState::Attack && animationFinished) {
        currentState = AnimState::Idle;
        isAttacking = false;
    }

    anim.setScale(facingRight ? 4.f : -4.f, 4.f);

    // Utrzymywanie hitboxa na postaci
    sf::Vector2f newPos = anim.getPosition();
    hitbox.setPosition(newPos.x - hitbox.getSize().x / 2.f, newPos.y - hitbox.getSize().y / 2.f);
}

void Player::takeDamage(int damage) {
    if (invincibilityTimer <= 0.f) {
        hp -= damage;
        if (hp < 0) hp = 0;
        invincibilityTimer = 0.5f;
    }
}

void Player::heal(int amount) { hp += amount; if (hp > MAX_PLAYER_HP) hp = MAX_PLAYER_HP; }

void Player::draw(sf::RenderWindow& window) { anim.draw(window); }