#include "buttons.h"

Button::Button(sf::Vector2f position, float scale, const sf::Texture& texture, std::function<void()> action) {
    onClickAction = action;
    isHovered = false;
    isSelected = false;

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);
}

Button::Button(sf::Vector2f position, float scaleX, float scaleY, const sf::Texture& texture, std::function<void()> action) {
    onClickAction = action;
    isHovered = false;
    isSelected = false;

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scaleX, scaleY);
}

// ZDIAGNOZOWANO I NAPRAWIONO: Automatyczne skalowanie ramki
void Button::setHoverTexture(const sf::Texture& hoverTexture) {
    hoverSprite.setTexture(hoverTexture);

    // Bierzemy prawdziwy rozmiar przycisku na ekranie
    sf::FloatRect bounds = sprite.getGlobalBounds();

    // Obliczamy skale dla ramki, by była o 16px szersza/wyższa (8px marginesu na każdą stronę)
    sf::Vector2u texSize = hoverTexture.getSize();
    float targetWidth = bounds.width + 16.f;
    float targetHeight = bounds.height + 16.f;

    hoverSprite.setScale(targetWidth / texSize.x, targetHeight / texSize.y);
    hoverSprite.setPosition(bounds.left - 8.f, bounds.top - 8.f);
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
        if (isHovered && onClickAction) {
            onClickAction();
        }
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);

    // Rysuje ramkę, jeśli najeżdżamy myszką LUB jeśli przycisk jest wybrany (kliknięty)
    if ((isHovered || isSelected) && hoverSprite.getTexture() != nullptr) {
        window.draw(hoverSprite);
    }
}