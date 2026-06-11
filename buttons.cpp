#include "buttons.h"

Button::Button(sf::Vector2f position, float scale, const sf::Texture& texture, std::function<void()> action) {
    onClickAction = action;

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);
}

void Button::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (sprite.getGlobalBounds().contains(mousePosF)) {
            if (onClickAction) {
                onClickAction();
            }
        }
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
