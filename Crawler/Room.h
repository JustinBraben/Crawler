#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class Room {
public:
    // Constructor
    Room(float startX, float startY, float roomWidth, float roomHeight, const std::string& tilesetPath, int startTileSize)
        : x(startX), y(startY), width(roomWidth), height(roomHeight), tileSize(startTileSize)
    {
        // Load the tileset texture
        if (!tileset.loadFromFile(tilesetPath)) {
            std::cerr << "Failed to load tileset: " << tilesetPath << std::endl;
            // Error handling
        }

        tiles.resize(width);
        for (auto& tile : tiles)
            tile.resize(height);
    }

    // Accessors
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    sf::Texture& getTileset() { return tileset; }
    std::vector<std::vector<sf::Sprite>>& getTiles() { return tiles; }

    // Mutators
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setTile(int col, int row, sf::IntRect textRect) {
        if (col >= 0 && col < width && row >= 0 && row < height) {
            sf::Sprite& sprite = tiles[col][row];
            sprite.setTexture(tileset);
            sprite.setTextureRect(textRect);
            sprite.setPosition(col * tileSize, row * tileSize);
        }
    }

    // Member functions
    void draw(sf::RenderWindow& window) {
        for (int col = 0; col < width; ++col) {
            for (int row = 0; row < height; ++row) {
                window.draw(tiles[col][row]);
            }
        }
    }

    // Get IntRect for tile mapping textures
    sf::IntRect getTextureRect(int x, int y) const {
        return sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize);
    }

private:
    float x, y;
    int width, height;
    int tileSize;
    sf::Texture tileset;
    std::vector<std::vector<sf::Sprite>> tiles;
};