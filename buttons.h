#ifndef BUTTONS_H
#define BUTTONS_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    sf::Sprite sprite;
    std::function<void()> onClickAction;

public:
    Button(sf::Vector2f position, float scale, const sf::Texture& texture, std::function<void()> action);

    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif
