#pragma once
#include <SFML/Graphics.hpp>
class Player {
public:
    // Constructors
    Player(float startX, float startY, int startHealth, const std::string& spritePath) {
        x = startX;
        y = startY;
        health = startHealth;
        if (!texture.loadFromFile(spritePath)) {
            // Error handling
        }
        isFacingRight = true;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(1 * 24, 1 * 24, 24, 24));
        sprite.setOrigin(sprite.getPosition().x + 12.0f, sprite.getPosition().x + 12.0f);
        setPosition();
    }

    // Accessors
    float getX() const { return x; }
    float getY() const { return y; }
    int getHealth() const { return health; }

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

    void update(sf::Time deltaTime) {
        // Calculate movement based on deltaTime
        float movementSpeed = 100.0f;
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

