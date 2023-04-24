#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>

class RoomManager {
public:
    // Constructor
    RoomManager(int numRoomsX, int numRoomsY, int roomWidth, int roomHeight, int tileSize, const sf::Texture& tileset, int currentRoomId = 0) :
        playerRoom(nullptr), rooms()
    {
        int curRoomCount = 0;
        for (int i = 0; i < numRoomsX; ++i) {
            for (int j = 0; j < numRoomsY; ++j) {
                createRoom(i, j, numRoomsX, numRoomsY, roomWidth, roomHeight, tileSize, tileset, curRoomCount);
                curRoomCount++;
            }
        }

        // Link doors between adjacent rooms
        for (int i = 0; i < numRoomsX; ++i) {
            for (int j = 0; j < numRoomsY; ++j) {
                int roomId = i * numRoomsY + j;
                if (i > 0) {
                    createAndLinkDoors(roomId, roomId - numRoomsY);
                }
                if (j > 0) {
                    createAndLinkDoors(roomId, roomId - 1);
                }
            }
        }

        // Set the first room as the player room
        if (!rooms.empty()) {
            playerRoom = rooms.at(0);
        }
    }

    // Accessors
    const std::unordered_map<int, std::shared_ptr<Room>> getRooms() const { return rooms; }
    auto getPlayerRoom() const { return playerRoom; }

    // Member functions
    void draw(sf::RenderWindow& window) {
        playerRoom->draw(window);
    }

    void createRoom(float startX, float startY, int numRoomsX, int numRoomsY, int roomWidth, int roomHeight, int tileSize, const sf::Texture& tileset, int currentRoomId = 0) {
        // Make a random number between 1 and 15 inclusive to represent the row of textureRects to pick from
        std::random_device rd;  // seed the random number generator
        std::mt19937 gen(rd());  // Mersenne Twister 19937 generator
        std::uniform_int_distribution<> distrib(1, 15);  // distribution from 1 to 15 inclusive

        int randomTileTextureRow = distrib(gen);  // generate a random number

        // Generate random position and dimensions for the room
        float x = static_cast<float>(startX);
        float y = static_cast<float>(startY);
        int width = roomWidth;
        int height = roomHeight;
        int roomTileSize = tileSize;

        // Create the room
        auto room = std::make_shared<Room>(x * static_cast<float>(width), y * static_cast<float>(height), width, height, tileset, roomTileSize);

        // Add the room to the map of rooms
        rooms[currentRoomId] = room;
    }

    void createAndLinkDoors(int roomId1, int roomId2) {
        // Generate door positions for both rooms
        rooms[roomId1]->generateDoorPositions(roomId2);
        rooms[roomId2]->generateDoorPositions(roomId1);

        // Get the door positions from both rooms
        auto& room1Doors = rooms[roomId1]->getDoors();
        auto& room2Doors = rooms[roomId2]->getDoors();

        // Link the doors
        if (!room1Doors.empty() && !room2Doors.empty()) {
            room1Doors.back().linkedRoomId = roomId2;
            room1Doors.back().linkedPosition = room2Doors.back().position;
            room2Doors.back().linkedRoomId = roomId1;
            room2Doors.back().linkedPosition = room1Doors.back().position;
        }
    }

    void addDoor(int roomId, const Door& door) {
        rooms[roomId]->addDoor(door);
    }

private:
    std::shared_ptr<Room> playerRoom;
    std::unordered_map<int, std::shared_ptr<Room>> rooms;
    int currentRoomId;
};