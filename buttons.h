#ifndef BUTTONS_H
#define BUTTONS_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    sf::Sprite sprite;
    sf::Sprite hoverSprite;
    bool isHovered;
    bool isSelected;
    std::function<void()> onClickAction;

public:
    Button(sf::Vector2f position, float scale, const sf::Texture& texture, std::function<void()> action);
    Button(sf::Vector2f position, float scaleX, float scaleY, const sf::Texture& texture, std::function<void()> action);

    void setHoverTexture(const sf::Texture& hoverTexture);
    void setSelected(bool select);
    bool getSelected() const;
    sf::FloatRect getGlobalBounds() const;

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif