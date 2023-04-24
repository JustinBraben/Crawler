#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Tile.h"

struct Door {
    sf::Vector2i position; // Position of the door in the room
    int linkedRoomId; // ID of the room the door links to
    sf::Vector2i linkedPosition; // Position in the linked room where the player should appear after using the door
};


class Room {
public:
    // Constructor
    Room(float startX, float startY, int roomWidth, int roomHeight, const sf::Texture& givenTileTexture, int startTileSize)
        : x(startX), y(startY), width(static_cast<int>(startX) + roomWidth), height(static_cast<int>(startY) + roomHeight), tileset(givenTileTexture), tileSize(startTileSize)
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
    auto& getDoors() { return doors; }
    // Get IntRect for tile mapping textures
    sf::IntRect getTextureRect(int x, int y) const {
        return sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize);
    }
    std::vector<sf::Vector2i> getTilesOfType(TileType targetType) const {
        std::vector<sf::Vector2i> positions;

        for (size_t column = 0; column < tiles.size(); ++column) {
            for (size_t row = 0; row < tiles[column].size(); ++row) {
                if (tiles[column][row]->getType() == targetType) {
                    positions.emplace_back(column, row);
                }
            }
        }

        return positions;
    }

    // Mutators
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setTile(int col, int row, TileType type) {
        if (col >= x && col < width && row >= y && row < height) {
            //auto newTile = std::make_shared<Tile>(static_cast<float>(col), static_cast<float>(row), tileSize, tileset, type, tileTextureRects);
            //tiles[col - xStart][row - yStart] = newTile;
        }
    }

    void generateDoorPositions(int adjacentRoomId) {
        // Generate a door position on one of the room's sides (left, right, top, or bottom)
        // For example, we can randomly choose a side and position for the door
        // Make sure the door position is valid within the room boundaries

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> doorSideDist(0, 3);

        int doorSide = doorSideDist(gen); // Randomly choose a side (0: left, 1: right, 2: top, 3: bottom)

        int doorPosition;
        std::uniform_int_distribution<> doorPositionDist;
        Door newDoor;
        newDoor.linkedRoomId = adjacentRoomId;

        switch (doorSide) {
        case 0: // Left
            doorPositionDist = std::uniform_int_distribution<>(1, height - 2);
            doorPosition = doorPositionDist(gen);
            newDoor.position = sf::Vector2i(0, doorPosition);
            break;
        case 1: // Right
            doorPositionDist = std::uniform_int_distribution<>(1, height - 2);
            doorPosition = doorPositionDist(gen);
            newDoor.position = sf::Vector2i(width - 1, doorPosition);
            break;
        case 2: // Top
            doorPositionDist = std::uniform_int_distribution<>(1, width - 2);
            doorPosition = doorPositionDist(gen);
            newDoor.position = sf::Vector2i(doorPosition, 0);
            break;
        case 3: // Bottom
            doorPositionDist = std::uniform_int_distribution<>(1, width - 2);
            doorPosition = doorPositionDist(gen);
            newDoor.position = sf::Vector2i(doorPosition, height - 1);
            break;
        }

        // Add the door to the doors vector
        doors.push_back(newDoor);

        //setTile(newDoor.position.x, newDoor.position.y, TileType::Door);
    }

    Door generateDoor() {
        auto floorPositions = getTilesOfType(TileType::Floor);

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(floorPositions.begin(), floorPositions.end(), g);

        for (const auto& floorPos : floorPositions) {
            int col = floorPos.x;
            int row = floorPos.y;
            int radius = 1;
            bool hasAdjacentFloors = isTileType(col - radius, row, TileType::Floor) &&
                isTileType(col + radius, row, TileType::Floor) &&
                isTileType(col, row - radius, TileType::Floor) &&
                isTileType(col, row + radius, TileType::Floor);

            if (hasAdjacentFloors) {
                // This is a valid door position
                Door door;
                door.position = sf::Vector2i(col, row);
                return door;
            }
        }

        // In case no valid position was found, return a door with an invalid position
        Door invalidDoor;
        invalidDoor.position = sf::Vector2i(-1, -1);
        return invalidDoor;
    }

    // Member functions
    void draw(sf::RenderWindow& window) {
        for (auto line : tiles) {
            for (auto tile : line) {
                tile->draw(window);
            }
        }
    }

    void randomizeTiles() {
        // Make a random number between 1 and 15 inclusive to represent the row of textureRects to pick from
        std::random_device rd;  // seed the random number generator
        std::mt19937 gen(rd());  // Mersenne Twister 19937 generator
        std::uniform_int_distribution<> distrib(1, 15);  // distribution from 1 to 15 inclusive

        int randomTileTextureRow = distrib(gen);  // generate a random number

        // Loop through 1 to 27 inclusive and add textureRects to your tileTextureRects
        for (int i = 1; i < 28; i++) {
            sf::IntRect textureRect = getTextureRect(i, randomTileTextureRow);
            tileTextureRects.emplace_back(textureRect);
        }

        for (int col = static_cast<int>(x); col < width; col++) {

            std::vector<std::shared_ptr<Tile>> lineOfTiles;

            for (int row = static_cast<int>(y); row < height; row++) {

                if (col == static_cast<int>(x) || col == width - 1 || row == static_cast<int>(y) || row == height - 1) { // if it's an outside tile
                    auto tempTile = std::make_shared<Tile>(col, row, tileSize, tileset, TileType::Wall, tileTextureRects);
                    lineOfTiles.emplace_back(tempTile);
                }
                else {
                    // Generate a random number between 0 and 99
                    std::uniform_int_distribution<> tileDistrib(0, 99); // distribution from 0 to 99 inclusive
                    int randomNumber = tileDistrib(gen);

                    if (randomNumber < 20) { // 20% chance of being a wall 
                        auto tempTile = std::make_shared<Tile>(col, row, tileSize, tileset, TileType::Wall, tileTextureRects);
                        lineOfTiles.emplace_back(tempTile);
                        //std::cout << "wall at position: " << col << ", " << row << "\n";
                        //std::cout << "center of wall is : " << tempTile.getCenterLocation2f().x << ", " << tempTile.getCenterLocation2f().y << "\n";
                    }
                    else {
                        lineOfTiles.emplace_back(std::make_shared<Tile>(col, row, tileSize, tileset, TileType::Floor, tileTextureRects)); // floor texture coordinates
                    }
                }
            }

            tiles.emplace_back(lineOfTiles);
        }
    }
    bool containsPosition(const std::vector<sf::Vector2i>& positions, const sf::Vector2i& pos) {
        return std::find(positions.begin(), positions.end(), pos) != positions.end();
    }
    void removePosition(std::vector<sf::Vector2i>& positions, const sf::Vector2i& pos) {
        if (containsPosition(positions, pos)) {
            positions.erase(std::remove(positions.begin(), positions.end(), pos), positions.end());
        }
    }
    bool isTileType(int col, int row, TileType tileTypeCheck) {
        sf::Vector2i pos(col, row);
        if (col < x || col >= width || row < y || row >= height) {
            return true;
        }
        return containsPosition(getTilesOfType(tileTypeCheck), pos);
    }

    void addDoor(const Door& door) {
        doors.push_back(door);
    }
private:
    int x, y;                                                   // Top left corner coordinates for the room
    int width, height;                                          // Width/Height of the board
    int tileSize;                                               // Size of the tiles
    sf::Texture tileset;                                        // Texture for the tiles
    std::vector<sf::IntRect> tileTextureRects;                  // Int Rects for the Texture of the tiles
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;      // 2D vector of Tiles for the room
    std::vector<Door> doors;
};