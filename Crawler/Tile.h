#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

enum class TileType {
    Wall,
    Floor,
    Door
};

class Tile
{
public:
    Tile(float startX, float startY, int startTileSize, const sf::Texture& givenTileTexture, TileType type, const std::vector<sf::IntRect> tileTextureRects, float hbOffset = 2.0f) :
        x(startX), y(startY), tileSize(startTileSize), tileType(type), hitboxOffset(hbOffset) {

        // Set the tileTexture
        tileSprite.setTexture(givenTileTexture);

        // Set the tile's position based on the constructor parameters, adjust based on tileSize
        setPosition(startX * tileSize, startY * tileSize);

        switch (tileType) {
        case TileType::Wall:
            tileSprite.setTextureRect(tileTextureRects[9]); // wall texture coordinates
            break;
        case TileType::Floor:
            tileSprite.setTextureRect(tileTextureRects[4]);  // floor texture coordinates
            break;
        case TileType::Door:
            tileSprite.setTextureRect(getTextureRect(29, 3)); // door texture coordinates
            break;
        }
    }

    // Accessors
    float getX() const { return x; }
    float getY() const { return y; }
    TileType getType() const { return tileType; }
    sf::IntRect getTextureRect(int x, int y) const { return sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize); } // Get IntRect for tile mapping textures
    sf::Vector2f getCenterLocation2f() {
        float halfTile = static_cast<float>(tileSize / 2.0f);
        return sf::Vector2f(static_cast<float>(getX() + halfTile), static_cast<float>(getY() + halfTile));  // Will use this when Calculating distance
    }
    sf::Vector2f getTopLeft() { return sf::Vector2f(tileSprite.getGlobalBounds().left, tileSprite.getGlobalBounds().top); }
    sf::FloatRect getTileHitBox() {
        float halfTile = static_cast<float>(tileSize / 2.0f);
        return sf::FloatRect(getTopLeft().x + halfTile + hitboxOffset,
            getTopLeft().y + halfTile + hitboxOffset,
            tileSize - (2.0f * hitboxOffset),
            tileSize - (2.0f * hitboxOffset)
        );
    }

    // Mutators
    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        tileSprite.setPosition(x, y);
    }

    // Member Functions
    void draw(sf::RenderWindow& window) {
        window.draw(tileSprite);
    }

private:
    float x, y, hitboxOffset;
    int tileSize;
    TileType tileType;
    sf::Texture tileTexture;
    sf::Sprite tileSprite;
};
