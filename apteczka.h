#ifndef APTECZKA_H
#define APTECZKA_H

#include "gameobject.h"

class Apteczka : public GameObject {
private:
    sf::RectangleShape shape;
    bool active;

public:
    Apteczka(float x, float y);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() override;
    bool isActive() override;

    void collect();
};

#endif