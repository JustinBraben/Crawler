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
    const std::vector<sf::Vector2i>& getWallPositions() const { return wallPositions; }
    const std::vector<sf::Vector2i>& getDoorPositions() const { return doorPositions; }

    // Mutators
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setTile(int col, int row, sf::IntRect textRect) {
        if (col >= 0 && col < width && row >= 0 && row < height) {
            sf::Sprite& sprite = tiles[col][row];
            sprite.setTexture(tileset);
            sprite.setTextureRect(textRect);
            //sprite.setOrigin(tileSize / 2.f, tileSize / 2.f); // Add this line to set the origin
            sprite.setPosition(col * tileSize, row * tileSize);
        }
    }
    void setDoor(int col, int row) {
        sf::IntRect textureRect = getTextureRect(29, 3); // Door texture rect is (29, 3) in tileset
        setTile(col, row, textureRect);
    }
    // Add this public member function to set the door positions
    void setDoorPositions(const std::vector<sf::Vector2i>& newDoorPositions) {
        doorPositions = newDoorPositions;
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
        const int numDoors = 2; // Set the number of doors you want to create
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int col = 0; col < width; ++col) {
            for (int row = 0; row < height; ++row) {
                sf::IntRect textureRect;

                if (col == 0 || col == width - 1 || row == 0 || row == height - 1) { // if it's an outside tile
                    textureRect = getTextureRect(10, 1); // wall texture coordinates
                    wallPositions.emplace_back(col, row);
                }
                else {
                    // Generate a random number between 0 and 99
                    int randomNumber = std::rand() % 100;

                    if (randomNumber < 20) { // 20% chance of being a wall tile
                        textureRect = getTextureRect(10, 1); // wall texture coordinates
                        wallPositions.emplace_back(col, row);
                    }
                    else {
                        textureRect = getTextureRect(5, 1); // floor texture coordinates
                    }
                }
                setTile(col, row, textureRect);
            }
        }

        // Generate random door positions
        for (int i = 0; i < numDoors; i++) {
            sf::Vector2i doorPos;
            do {
                doorPos.x = std::rand() % width;
                doorPos.y = std::rand() % height;
            } while (isWallTile(doorPos.x, doorPos.y));

            // Check if there is a wall in the same position as the new door
            auto it = std::find(wallPositions.begin(), wallPositions.end(), doorPos);
            if (it != wallPositions.end()) {
                wallPositions.erase(it); // Remove the wall if it exists
            }

            setDoor(doorPos.x, doorPos.y);
            doorPositions.push_back(doorPos);
        }

        setDoorPositions(doorPositions); // Set the door positions in the member variable
    }

    bool isWallTile(int col, int row) const {
        // Check if the tile at the given position is a wall tile
        if (col < 0 || col >= width || row < 0 || row >= height) {
            // Out of bounds, treat as a wall tile
            return true;
        }
        return false;
    }

    sf::Vector2f getTileCenter(sf::Vector2i& wallPosition) {
        float centerX = wallPosition.x + tileSize / 2;
        float centerY = wallPosition.y + tileSize / 2;
        return sf::Vector2f(centerX, centerY);
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
    std::vector<sf::Vector2i> wallPositions; // 2D vector of wall positions
    std::vector<sf::Vector2i> doorPositions; // 2D vector of door positions
};