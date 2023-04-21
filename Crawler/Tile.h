#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class TileType {
    Wall,
    Floor,
    Door
};

class Tile
{
public:
    Tile(float startX, float startY, int startTileSize, const sf::Texture& givenTileTexture, TileType type, float hbOffset = 2.0f) :
        x(startX), y(startY), tileSize(startTileSize), tileType(type), hitboxOffset(hbOffset) {

        // Set the tileTexture
        tileSprite.setTexture(givenTileTexture);

        // Set the tile's position based on the constructor parameters, adjust based on tileSize
        setPosition(startX * tileSize, startY * tileSize);

        // Set the texture rect based on the tile type
        sf::IntRect textureRect;
        switch (tileType) {
        case TileType::Wall:
            textureRect = getTextureRect(10, 1); // wall texture coordinates
            break;
        case TileType::Floor:
            textureRect = getTextureRect(5, 1);  // floor texture coordinates
            break;
        case TileType::Door:
            textureRect = getTextureRect(29, 3); // door texture coordinates
            break;
        }
        tileSprite.setTextureRect(textureRect);
    }

    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
        tileSprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(tileSprite);
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    TileType getType() const {
        return tileType;
    }

    // Get IntRect for tile mapping textures
    sf::IntRect getTextureRect(int x, int y) const {
        return sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize);
    }

    // Will use this when Calculating distance
    sf::Vector2f getCenterLocation2f() {
        float halfTile = static_cast<float>(tileSize / 2.0f);
        return sf::Vector2f(static_cast<float>(getX() + halfTile), static_cast<float>(getY() + halfTile));
        //return sf::Vector2f(static_cast<float>(halfTile + tileSize * x), static_cast<float>(halfTile + tileSize * y));
    }

    sf::Vector2f getTopLeft() {
        return sf::Vector2f(tileSprite.getGlobalBounds().left, tileSprite.getGlobalBounds().top);
    }

    sf::FloatRect getTileHitBox() {
        float halfTile = static_cast<float>(tileSize / 2.0f);
        return sf::FloatRect(getTopLeft().x + halfTile + hitboxOffset,
            getTopLeft().y + halfTile + hitboxOffset,
            tileSize - (2.0f * hitboxOffset), 
            tileSize - (2.0f * hitboxOffset)
        );
    }

private:
    float x, y, hitboxOffset;
    int tileSize;
    TileType tileType;
    sf::Texture tileTexture;
    sf::Sprite tileSprite;
};
