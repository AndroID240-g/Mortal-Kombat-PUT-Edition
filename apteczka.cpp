#include "apteczka.h"

Apteczka::Apteczka(float x, float y) {
    shape.setSize(sf::Vector2f(30.f, 30.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
    active = true;
}

void Apteczka::update(float deltaTime) {
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