#include "apteczka.h"
#include "config.h" // Konieczne do pobrania APTECZKA_ROTATION_SPEED

Apteczka::Apteczka(float x, float y) {
    shape.setSize(sf::Vector2f(30.f, 30.f));
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(15.f, 15.f); // DODANE: Środek rotacji obiektu (połowa rozmiaru)
    shape.setPosition(x, y);
    active = true;
    rotationSpeed = APTECZKA_ROTATION_SPEED;
}

void Apteczka::update(float deltaTime) {
    // Aplikowanie rotacji z użyciem czasu (stopnie/sekundę)
    shape.setRotation(shape.getRotation() + rotationSpeed * deltaTime);
}

void Apteczka::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect Apteczka::getBounds() {
    return shape.getGlobalBounds();
}

bool Apteczka::isActive() {
    return active;
}

void Apteczka::collect() {
    active = false;
}