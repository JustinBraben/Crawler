#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <random>
#include <algorithm>

class RoomManager {
public:
    // Constructor
    RoomManager(int numRooms, const sf::Texture& tileset) {
        for (int i = 0; i < numRooms; ++i) {
            // Generate random position and dimensions for the room
            float x = static_cast<float>(std::rand() % 800);
            float y = static_cast<float>(std::rand() % 600);
            int width = std::rand() % 4 + 4;
            int height = std::rand() % 4 + 4;
            int tileSize = std::rand() % 4 + 4;
            int textureRow = std::rand() % 15 + 1;

            // Create the room
            Room room(x, y, width, height, tileset, tileSize);
            //room.randomizeTiles();
            room.setDoorPositions(generateDoorPositions(room));

            // Add the room to the vector of rooms
            rooms.push_back(room);
        }
    }

    // Accessors
    const std::vector<Room>& getRooms() const { return rooms; }

private:
    std::vector<Room> rooms;
    // Helper function to generate door positions for a room
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
};


