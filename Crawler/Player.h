#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"
class Player {
public:
    // Constructors
    Player(float startX, float startY, int startHealth, const std::string& spritePath, const Room& room) {
        x = startX;
        y = startY;
        health = startHealth;
        if (!texture.loadFromFile(spritePath)) {
            // Error handling
        }
        isFacingRight = true;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(1 * 24, 1 * 24, 24, 24));

        // Check if the starting position collides with any wall tiles in the room
        const float offset = 8.0f; // Adjust this value to change the offset
        bool isColliding = false;
        for (const auto& wallPos : room.getWallPositions()) {
            if (x + sprite.getLocalBounds().width > wallPos.x * room.getTileSize() + offset &&
                x < (wallPos.x + 1) * room.getTileSize() - offset &&
                y + sprite.getLocalBounds().height > wallPos.y * room.getTileSize() + offset &&
                y < (wallPos.y + 1) * room.getTileSize() - offset) {
                isColliding = true;
                break; // Found a wall tile that collides with the starting position
            }
        }

        // If the starting position collides with a wall tile, nudge the player to a nearby tile
        while (isColliding) {
            x += room.getTileSize();
            if (x + sprite.getLocalBounds().width > room.getWidth() * room.getTileSize()) {
                x = 0;
                y += room.getTileSize();
            }
            if (y + sprite.getLocalBounds().height > room.getHeight() * room.getTileSize()) {
                y = 0;
            }

            // Check if the new position collides with any wall tiles in the room
            isColliding = false;
            for (const auto& wallPos : room.getWallPositions()) {
                if (x + sprite.getLocalBounds().width > wallPos.x * room.getTileSize() + offset &&
                    x < (wallPos.x + 1) * room.getTileSize() - offset &&
                    y + sprite.getLocalBounds().height > wallPos.y * room.getTileSize() + offset &&
                    y < (wallPos.y + 1) * room.getTileSize() - offset) {
                    isColliding = true;
                    break; // Found a wall tile that collides with the new position
                }
            }
        }

        sprite.setOrigin(sprite.getPosition().x + 12.0f, sprite.getPosition().x + 12.0f);
        setPosition();
    }

    // Accessors
    float getX() const { return x; }
    float getY() const { return y; }
    int getHealth() const { return health; }
    sf::Vector2f getPlayerCenter() {
        const sf::FloatRect& bounds = sprite.getLocalBounds();
        float centerX = getX() + bounds.width / 2;
        float centerY = getY() + bounds.height / 2;
        return sf::Vector2f(centerX, centerY);
    }
    sf::Vector2f getPlayerCenter(const Player& player) {
        const sf::FloatRect& bounds = player.sprite.getLocalBounds();
        float centerX = player.getX() + bounds.width / 2;
        float centerY = player.getY() + bounds.height / 2;
        return sf::Vector2f(centerX, centerY);
    }

    // Mutators
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setPosition()  { sprite.setPosition(sf::Vector2f(x, y)); }
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

        // Check if the new position is within the outer walls
        if (nextX < 0 ||
            nextY < 0 ||
            nextX + sprite.getLocalBounds().width > room.getWidth() * room.getTileSize() ||
            nextY + sprite.getLocalBounds().height > room.getHeight() * room.getTileSize()) {
            return; // Don't move outside the outer walls
        }

        // Check if the new position collides with any wall tiles in the room
        const float offset = 8.0f; // Adjust this value to change the offset
        for (const auto& wallPos : room.getWallPositions()) {
            if (nextX + sprite.getLocalBounds().width > wallPos.x * room.getTileSize() + offset &&
                nextX < (wallPos.x + 1) * room.getTileSize() - offset &&
                nextY + sprite.getLocalBounds().height > wallPos.y * room.getTileSize() + offset &&
                nextY < (wallPos.y + 1) * room.getTileSize() - offset) {
                return; // Don't move into wall tiles
            }
        }

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
    int health;
    bool isFacingRight;
    sf::Texture texture;
    sf::Sprite sprite;
};

