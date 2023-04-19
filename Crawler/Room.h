#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

        randomizeTiles();
    }

    // Accessors
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTileSize() const { return tileSize; }
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

    void randomizeTiles() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int col = 0; col < width; ++col) {
            for (int row = 0; row < height; ++row) {
                sf::IntRect textureRect;

                if (col == 0 || col == width - 1 || row == 0 || row == height - 1) { // if it's an outside tile
                    textureRect = getTextureRect(10, 1); // wall texture coordinates
                }
                else {
                    // Generate a random number between 0 and 99
                    int randomNumber = std::rand() % 100;

                    if (randomNumber < 20) { // 20% chance of being a wall tile
                        textureRect = getTextureRect(10, 1); // wall texture coordinates
                    }
                    else {
                        textureRect = getTextureRect(5, 1); // floor texture coordinates
                    }
                }
                setTile(col, row, textureRect);
            }
        }
    }

    bool isWallTile(int col, int row) const {
        // Check if the tile at the given position is a wall tile
        if (col < 0 || col >= width || row < 0 || row >= height) {
            // Out of bounds, treat as a wall tile
            return true;
        }
        //auto checkSprite = tiles[col][row];
        //sf::IntRect textureRect = checkSprite.getTextureRect();

        // Check if the texture rect corresponds to a wall tile
        //return textureRect == getTextureRect(5, 1); // Assuming wall texture rect is (5, 1) in your tileset
        return false;
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