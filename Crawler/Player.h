#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"
class Player {
public:
    // Constructors
    Player(float startX, float startY, int startHealth, int playerSize, const std::string& spritePath, Room& room) {
        x = startX;
        y = startY;
        tileSize = playerSize;
        health = startHealth;
        if (!texture.loadFromFile(spritePath)) {
            // Error handling
        }
        float halfTileSize = static_cast<float>(tileSize / 2.0f);
        isFacingRight = true;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(tileSize, tileSize, tileSize, tileSize));
        sprite.setOrigin(halfTileSize, halfTileSize);
        //sprite.setOrigin(sprite.getPosition().x + tileSize / 2.0f, sprite.getPosition().x + tileSize / 2.0f); // working line, but why
        setPosition();
    }

    // Accessors
    auto getX() const { return x; }
    auto getY() const { return y; }
    float getDistance(sf::Vector2f tar1, sf::Vector2f tar2) {
        float dx = tar2.x - tar1.x;
        float dy = tar2.y - tar1.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    int getHealth() const { return health; }
    sf::Vector2f getPlayerCenter() {
        float halfPlayerSize = static_cast<float>(tileSize / 2.0f);
        return sf::Vector2f(static_cast<float>(getX()), static_cast<float>(getY()));
    }

    // Mutators
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setPosition()  { 
        //sprite.setOrigin(getPlayerCenter().x, getPlayerCenter().y);
        sprite.setPosition(sf::Vector2f(x, y)); 
    }
    void setHealth(int newHealth)   { health = newHealth; }

    // Member functions
    void move(float dx, float dy) {
        x += dx;
        y += dy;
    }

    void takeDamage(int damage) {
        health -= damage;
    }

    void update(Room& room, sf::Time deltaTime) {
        // Calculate movement based on deltaTime
        float movementSpeed = 150.0f;
        float dx = 0, dy = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dx = -1.0f;
            isFacingRight = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dx = 1.0f;
            isFacingRight = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dy = -1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dy = 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            getPlayerCenter();
            std::cout << "Player center: " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
        }

        float nextX = x + dx * movementSpeed * deltaTime.asSeconds();
        float nextY = y + dy * movementSpeed * deltaTime.asSeconds();

        move(dx * movementSpeed * deltaTime.asSeconds(), dy * movementSpeed * deltaTime.asSeconds());

        // Update any other necessary data

        if (!isFacingRight) {
            sprite.setScale(1.0f, 1.0f);
        }
        else {
            sprite.setScale(-1.0f, 1.0f);
        }

        setPosition();
    }


    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    float x, y;
    int health, tileSize;
    bool isFacingRight;
    sf::Texture texture;
    sf::Sprite sprite;
};

