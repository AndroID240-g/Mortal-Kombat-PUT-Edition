#include "animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Animation::Animation(const std::string& texturePath, int width, int height, bool useMask, sf::Color maskColor) {
    frameWidth = width;
    frameHeight = height;
    currentFrame = 0;
    currentRow = 0;
    maxFrames = 1;
    animationTimer = 0.f;
    animationSpeed = 0.15f;

    sf::Image image;
    if (!image.loadFromFile(texturePath)) {
        std::cout << "Blad ladowania grafiki: " << texturePath << std::endl;
    }

    if (useMask) {
        image.createMaskFromColor(maskColor);
    }

    texture.loadFromImage(image);
    texture.setSmooth(false);

    sprite.setTexture(texture);
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

bool Animation::update(float deltaTime) {
    bool finished = false;
    animationTimer += deltaTime;

    if (animationTimer >= animationSpeed) {
        currentFrame++;
        animationTimer = 0.f;

        if (currentFrame >= maxFrames) {
            currentFrame = 0;
            finished = true;
        }
    }

    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, currentRow * frameHeight, frameWidth, frameHeight));
    return finished;
}

void Animation::setAnimation(int row, int frames, float originYOffset) {
    if (currentRow != row || maxFrames != frames) {
        currentRow = row;
        maxFrames = frames;
        currentFrame = 0;
        animationTimer = 0.f;
    }
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f + originYOffset);
}

void Animation::setSpeed(float speed) {
    animationSpeed = speed;
}

void Animation::setPosition(float x, float y) { sprite.setPosition(x, y); }
void Animation::setScale(float x, float y) { sprite.setScale(x, y); }
void Animation::move(float offsetX, float offsetY) { sprite.move(offsetX, offsetY); }
sf::Vector2f Animation::getPosition() const { return sprite.getPosition(); }
sf::FloatRect Animation::getGlobalBounds() const { return sprite.getGlobalBounds(); }
void Animation::draw(sf::RenderWindow& window) { window.draw(sprite); }