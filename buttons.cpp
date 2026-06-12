#include "buttons.h"

Button::Button(sf::Vector2f position, float scale, const sf::Texture& texture, std::function<void()> action) {
    onClickAction = action;
    isHovered = false;
    isSelected = false;

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);

    hoverSprite.setPosition(position);
    hoverSprite.setScale(scale, scale);
}

Button::Button(sf::Vector2f position, float scaleX, float scaleY, const sf::Texture& texture, std::function<void()> action) {
    onClickAction = action;
    isHovered = false;
    isSelected = false;

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scaleX, scaleY);

    hoverSprite.setPosition(position);
    hoverSprite.setScale(scaleX, scaleY);
}

void Button::setHoverTexture(const sf::Texture& hoverTexture) {
    hoverSprite.setTexture(hoverTexture);
}

void Button::setSelected(bool select) {
    isSelected = select;
}

bool Button::getSelected() const {
    return isSelected;
}

sf::FloatRect Button::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Button::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    isHovered = sprite.getGlobalBounds().contains(mousePosF);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isHovered) {
            if (onClickAction) {
                onClickAction();
            }
        }
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);

    if ((isHovered || isSelected) && hoverSprite.getTexture() != nullptr) {
        window.draw(hoverSprite);
    }
}