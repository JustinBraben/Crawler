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
        halfTileSize = static_cast<float>(tileSize / 2);
        health = startHealth;
        if (!texture.loadFromFile(spritePath)) {
            // Error handling
        }
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
        return sf::Vector2f(static_cast<float>(getX()), static_cast<float>(getY()));
    }

    sf::Vector2f getPlayerTopLeft() {
        return sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    }
    

    // Mutators
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setPosition() {
        //sprite.setOrigin(getPlayerCenter().x, getPlayerCenter().y);
        sprite.setPosition(sf::Vector2f(x, y));
    }
    void setPosition(float xPos, float yPos)  { 
        //sprite.setOrigin(getPlayerCenter().x, getPlayerCenter().y);
        x += xPos;
        y += yPos;
        sprite.setPosition(sf::Vector2f(x, y)); 
    }
    void setHealth(int newHealth)   { health = newHealth; }

    void takeDamage(int damage) {
        health -= damage;
    }

    sf::Vector2i getPlayerTile() {
        sf::Vector2i playerTile(static_cast<int>((getPlayerCenter().x - halfTileSize) / halfTileSize),
            static_cast<int>((getPlayerCenter().y - halfTileSize) / halfTileSize));
        return playerTile;
    }

    bool checkCollision(float nextX, float nextY, Room& room) {
        auto& tileSet = room.getTiles();
        sf::Vector2f vec2fTileSize(tileSize, tileSize);
        sf::FloatRect playerHitbox(getPlayerTopLeft(), vec2fTileSize);
        for (auto& line : tileSet) {
            for (auto& tile : line) {
                if (tile.getType() == TileType::Wall) {
                    sf::FloatRect tileHitbox(tile.getTopLeft(), vec2fTileSize);
                    if (playerHitbox.intersects(tileHitbox)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }



    void update(Room& room, sf::Time deltaTime, sf::Event evnt) {
        float movementSpeed = 150.0f;
        float dxMovement = 0.0f;
        float dyMovement = 0.0f;
        /*
        switch (evnt.type) {
            case sf::Event::KeyPressed:
                switch (evnt.key.code) {
                    case sf::Keyboard::A:
                        dxMovement -= 1.0f;
                        isFacingRight = false;
                        break;
                    case sf::Keyboard::D:
                        dxMovement += 1.0f;
                        isFacingRight = true;
                        break;
                    case sf::Keyboard::W:
                        dyMovement -= 1.0f;
                        break;
                    case sf::Keyboard::S:
                        dyMovement += 1.0f;
                        break;
                }
                break;
        }
        */
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            dxMovement -= 1.0f;
            isFacingRight = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            dxMovement += 1.0f;
            isFacingRight = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            dyMovement -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            dyMovement += 1.0f;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            getPlayerCenter();
            std::cout << "Player center is in position : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
            std::cout << "Player sprite is in position : left " << sprite.getGlobalBounds().left << ", top " << sprite.getGlobalBounds().top << "\n";
            //std::cout << "Player center is in tile : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
        }

        if (!isFacingRight) {
            sprite.setScale(1.0f, 1.0f);
        }
        else {
            sprite.setScale(-1.0f, 1.0f);
        }

        float nextX = x + dxMovement * movementSpeed * deltaTime.asSeconds();
        float nextY = y + dyMovement * movementSpeed * deltaTime.asSeconds();

        x = nextX;
        y = nextY;

        if (!checkCollision(nextX, y, room)) {
            //x = nextX;
        }
        else {
            std::cout << "Player collided with tile here : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
        }

        if (!checkCollision(x, nextY, room)) {
            //y = nextY;
        }
        else {
            std::cout << "Player collided with tile here : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
        }

        setPosition();
    }



    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    float x, y, halfTileSize;
    int health, tileSize;
    bool isFacingRight;
    sf::Texture texture;
    sf::Sprite sprite;
};

