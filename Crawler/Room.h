#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Tile.h"

class Room {
public:
    // Constructor
    Room(float startX, float startY, int roomWidth, int roomHeight, const sf::Texture& givenTileTexture, int startTileSize)
        : x(startX), y(startY), width(roomWidth), height(roomHeight), tileset(givenTileTexture), tileSize(startTileSize)
    {
        randomizeTiles();
    }

    // Accessors
    auto getX() const { return x; }
    auto getY() const { return y; }
    auto getWidth() const { return width; }
    auto getHeight() const { return height; }
    auto getTileSize() const { return tileSize; }
    const auto& getTileset() { return tileset; }
    auto& getTiles() { return tiles; }
    const std::vector<sf::Vector2i>& getWallPositions() const { return wallPositions; }
    const std::vector<sf::Vector2i>& getDoorPositions() const { return doorPositions; }

    // Mutators
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setTile(int col, int row, TileType type) {
        if (col >= 0 && col < width && row >= 0 && row < height) {
            auto& tile = tiles[col][row];
            tile = Tile(static_cast<float>(col), static_cast<float>(row), tileSize, tileset, type);
        }
    }

    // Add this public member function to set the door positions
    void setDoorPositions(const std::vector<sf::Vector2i>& newDoorPositions) {
        doorPositions = newDoorPositions;
    }

    // Member functions
    void draw(sf::RenderWindow& window) {
        for (auto line : tiles) {
            for (auto tile : line) {
                tile.draw(window);
            }
        }
    }

    void randomizeTiles() {
        const int numDoors = 2; // Set the number of doors you want to create
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int doorCount = 0;

        // Make a random number between 1 and 15 inclusive to represent the row of textureRects to pick from
        std::random_device rd;  // seed the random number generator
        std::mt19937 gen(rd());  // Mersenne Twister 19937 generator
        std::uniform_int_distribution<> distrib(1, 15);  // distribution from 1 to 15 inclusive

        int randomTileTextureRow = distrib(gen);  // generate a random number

        for (int col = 0; col < width; col++) {

            std::vector<Tile> lineOfTiles;

            for (int row = 0; row < height; row++) {

                if (col == 0 || col == width - 1 || row == 0 || row == height - 1) { // if it's an outside tile
                    auto tempTile = Tile(col, row, tileSize, tileset, TileType::Wall, randomTileTextureRow);
                    lineOfTiles.emplace_back(tempTile);
                    wallPositions.emplace_back(col, row);
                }
                else {
                    // Generate a random number between 0 and 99
                    std::uniform_int_distribution<> tileDistrib(0, 99); // distribution from 0 to 99 inclusive
                    int randomNumber = tileDistrib(gen);

                    if (randomNumber < 20) { // 20% chance of being a wall 
                        auto tempTile = Tile(col, row, tileSize, tileset, TileType::Wall, randomTileTextureRow);
                        lineOfTiles.emplace_back(tempTile);
                        wallPositions.emplace_back(col, row);
                        //std::cout << "wall at position: " << col << ", " << row << "\n";
                        //std::cout << "center of wall is : " << tempTile.getCenterLocation2f().x << ", " << tempTile.getCenterLocation2f().y << "\n";
                    }
                    else if (doorCount < 2 && (randomNumber < 22 && randomNumber > 20)) {
                        lineOfTiles.emplace_back(Tile(col, row, tileSize, tileset, TileType::Door, randomTileTextureRow));
                        doorCount++;
                        doorPositions.emplace_back(col, row);
                    }
                    else {
                        lineOfTiles.emplace_back(Tile(col, row, tileSize, tileset, TileType::Floor)); // floor texture coordinates
                    }
                }
            }

            tiles.emplace_back(lineOfTiles);
        }
    }

    /*
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
    */
private:
    float x, y;
    int width, height;
    int tileSize;
    sf::Texture tileset;
    std::vector<std::vector<Tile>> tiles;
    std::vector<sf::Vector2i> wallPositions; // 2D vector of wall positions
    std::vector<sf::Vector2i> doorPositions; // 2D vector of door positions
};