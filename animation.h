#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>

class Animation {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int currentRow;
    int maxFrames;
    float animationTimer;
    float animationSpeed;

public:
    Animation(const std::string& texturePath, int width, int height, bool useMask = false, sf::Color maskColor = sf::Color::Black);

    bool update(float deltaTime);
    void setAnimation(int row, int frames, float originYOffset = 0.f);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void move(float offsetX, float offsetY);
    void setSpeed(float speed);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderWindow& window);
};

#endif