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
        currentRoom = &room;

        // Check for collision with wall tiles at the start position
        while (checkCollision(x, y, room, TileType::Wall)) {
            x += static_cast<float>(tileSize);
            y += static_cast<float>(tileSize);
        }

        if (!texture.loadFromFile(spritePath)) {
            // Error handling
        }

        isFacingRight = true;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(tileSize, tileSize, tileSize, tileSize));
        sprite.setOrigin(halfTileSize, halfTileSize);
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
        sf::Vector2i playerTile(static_cast<int>(getPlayerCenter().x) / static_cast<int>(tileSize),
            static_cast<int>(getPlayerCenter().y) / static_cast<int>(tileSize)
        );
        return playerTile;
    }

    bool checkCollision(float nextX, float nextY, Room& room, TileType checkTileType, int radius = 1) {
        auto& tileSet = room.getTiles();
        sf::Vector2i playerTile = getPlayerTile();
        sf::Vector2f nextHitBoxPos(nextX, nextY);
        sf::Vector2f vec2fTileSize(tileSize, tileSize);
        sf::FloatRect nextHitbox(nextHitBoxPos, vec2fTileSize);

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int checkX = playerTile.x + i;
                int checkY = playerTile.y + j;
                if (checkX >= 0 && checkX < tileSet.size() && checkY >= 0 && checkY < tileSet[checkX].size()) {
                    Tile& tile = tileSet[checkX][checkY];
                    if (tile.getType() == checkTileType) {
                        sf::FloatRect tileHitbox = tile.getTileHitBox();
                        if (nextHitbox.intersects(tileHitbox)) {
                            return true;
                        }
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
        currentRoom = &room;
        
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
            //std::cout << "Player center is in position : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
            std::cout << "Player Tile is in position : " << getPlayerTile().x << ", " << getPlayerTile().y << "\n";
            //std::cout << "Player sprite is in position : left " << sprite.getGlobalBounds().left << ", top " << sprite.getGlobalBounds().top << "\n";
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

        // When moving in the x direction
        // if no collision detected in potential nextX location
        // update x coord of player sprite
        if (!checkCollision(nextX, y, room, TileType::Wall)) {
            x = nextX;
        }
        else {
            //std::cout << "Player collided with tile here : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
        }

        // When moving in the x direction
        // if no collision detected in potential nextX location
        // update y coord of player sprite
        if (!checkCollision(x, nextY, room, TileType::Wall)) {
            y = nextY;
        }
        else {
            //std::cout << "Player collided with tile here : " << getPlayerCenter().x << ", " << getPlayerCenter().y << "\n";
        }

        setPosition();
    }



    void draw(sf::RenderWindow& window, const Room& room) {
        if (currentRoom == &room) {
            window.draw(sprite);
        }
    }

private:
    float x, y, halfTileSize;
    int health, tileSize;
    bool isFacingRight;
    sf::Texture texture;
    sf::Sprite sprite;
    Room* currentRoom;
};

