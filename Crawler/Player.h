#pragma once
#include <SFML/Graphics.hpp>
class Player {
public:
    // Constructors
    Player(int startX, int startY, int startHealth, const std::string& spritePath) {
        x = startX;
        y = startY;
        health = startHealth;
        if (!texture.loadFromFile(spritePath)) {
            // Error handling
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(1 * 24, 1 * 24, 24, 24));
    }

    // Accessors
    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }

    // Mutators
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setHealth(int newHealth) { health = newHealth; }

    // Member functions
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void takeDamage(int damage) {
        health -= damage;
    }

    void update() {
        // Update any other necessary data
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    int x, y;
    int health;
    sf::Texture texture;
    sf::Sprite sprite;
};

