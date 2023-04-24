#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <memory>

class RoomManager {
public:
    // Constructor
    RoomManager(int numRoomsX, int numRoomsY, int roomWidth, int roomHeight, int tileSize, const sf::Texture& tileset) :
        playerRoom(nullptr)
    {
        for (int i = 0; i < numRoomsX; ++i) {
            for (int j = 0; j < numRoomsY; ++j) {
                // Make a random number between 1 and 15 inclusive to represent the row of textureRects to pick from
                std::random_device rd;  // seed the random number generator
                std::mt19937 gen(rd());  // Mersenne Twister 19937 generator
                std::uniform_int_distribution<> distrib(1, 15);  // distribution from 1 to 15 inclusive

                int randomTileTextureRow = distrib(gen);  // generate a random number

                // Generate random position and dimensions for the room
                float x = static_cast<float>(i);
                float y = static_cast<float>(j);
                int width = roomWidth;
                int height = roomHeight;
                int roomTileSize = tileSize;
                //int textureRow = std::rand() % 15 + 1;

                // Create the room
                auto room = std::make_shared<Room>(x * static_cast<float>(width), y * static_cast<float>(height), width, height, tileset, roomTileSize);

                //room.setDoorPositions(generateDoorPositions(room));

                // Add the room to the vector of rooms
                rooms.emplace_back(room);
            }
        }

        // Set the first room as the player room
        if (!rooms.empty()) {
            playerRoom = rooms.front();
        }
    }

    // Accessors
    const std::vector<std::shared_ptr<Room>> getRooms() const { return rooms; }
    auto getPlayerRoom() const { return playerRoom; }

    // Member functions
    void draw(sf::RenderWindow& window) {
        playerRoom->draw(window);
    }

private:
    std::vector<std::shared_ptr<Room>> rooms;
    std::shared_ptr<Room> playerRoom;
    // Helper function to generate door positions for a room
    /*
    std::vector<sf::Vector2i> generateDoorPositions(Room& room) {
        std::vector<sf::Vector2i> floorPositions = room.getFloorPositions();
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(floorPositions.begin(), floorPositions.end(), g);
        
        for (const auto& floorPos : floorPositions) {

            // Check if there is an adjacent floor tile in each direction
            int col = floorPos.x;
            int row = floorPos.y;
            bool hasAdjacentFloors = room.isTileType(col - 1, row, TileType::Floor) && 
                room.isTileType(col + 1, row, TileType::Floor) &&
                room.isTileType(col, row - 1, TileType::Floor) &&
                room.isTileType(col, row + 1, TileType::Floor);

            if (hasAdjacentFloors) {

                // This is a valid door position
                //floorPositions.push_back(floorPos);
                //if (doorPositions.size() == 2) {
                    // We have found two valid door positions, so we can stop searching
                //    break;
                //}
            }
        }
        
        return floorPositions;
    }
    */
};


