// Crawler.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Include SFML libraries and necessary headers
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "RoomManager.h"
#include "Camera.h"

// Define constants for window size, tile size, and other game settings
const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 600;
const int TILE_SIZE = 24;
const int NUM_TILES_X = WINDOW_WIDTH / TILE_SIZE;
const int NUM_TILES_Y = WINDOW_HEIGHT / TILE_SIZE;
const int NUM_ROOMS = 4;
const int MAX_ROOM_SIZE = 9;
const int MIN_ROOM_SIZE = 4;

// Define room struct
//struct Room {
//    int x, y;
//    int width, height;
//};
// Define functions for creating the map and generating rooms
//std::vector<Room> generateRooms();
//std::vector<std::vector<int>> createMap(std::vector<Room> rooms);
//void drawMap(std::vector<std::vector<int>> map, sf::RenderWindow& window);
//bool checkCollision(Room r1, Room r2);

// Function to generate the rooms for the map
//std::vector<Room> generateRooms() {
//    std::vector<Room> rooms;
//    // Generate the first room in the center of the map
//    Room firstRoom;
//    firstRoom.x = NUM_TILES_X / 2 - MIN_ROOM_SIZE / 2;
//    firstRoom.y = NUM_TILES_Y / 2 - MIN_ROOM_SIZE / 2;
//    firstRoom.width = MIN_ROOM_SIZE;
//    firstRoom.height = MIN_ROOM_SIZE;
//    rooms.push_back(firstRoom);
//    // Generate additional rooms
//    for (int i = 1; i < NUM_ROOMS; i++) {
//        bool roomAdded = false;
//        while (!roomAdded) {
//            // Generate random values for the room
//            Room newRoom;
//            newRoom.x = rand() % (NUM_TILES_X - MAX_ROOM_SIZE);
//            newRoom.y = rand() % (NUM_TILES_Y - MAX_ROOM_SIZE);
//            newRoom.width = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
//            newRoom.height = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
//
//            // Check if the new room overlaps with any existing rooms
//            bool overlap = false;
//            for (int j = 0; j < rooms.size(); j++) {
//                if (checkCollision(newRoom, rooms[j])) {
//                    overlap = true;
//                    break;
//                }
//            }
//
//            // If the new room doesn't overlap, add it to the list of rooms
//            if (!overlap) {
//                rooms.push_back(newRoom);
//                roomAdded = true;
//            }
//        }
//    }
//
//    return rooms;
//}

// Function to create the map from the list of rooms
//std::vector<std::vector<int>> createMap(std::vector<Room> rooms) {
//    std::vector<std::vector<int>> map(NUM_TILES_X, std::vector<int>(NUM_TILES_Y, 0));
//    // Set tiles in each room to 1
//    for (int i = 0; i < rooms.size(); i++) {
//        for (int x = rooms[i].x; x < rooms[i].x + rooms[i].width; x++) {
//            for (int y = rooms[i].y; y < rooms[i].y + rooms[i].height; y++) {
//                map[x][y] = 1;
//            }
//        }
//    }
//
//    return map;
//}

// Function to check if two rooms overlap
//bool checkCollision(Room r1, Room r2) {
//    return (r1.x < r2.x + r2.width &&
//        r1.x + r1.width > r2.x &&
//        r1.y < r2.y + r2.height &&
//        r1.y + r1.height > r2.y);
//}

// Function to draw the map
//void drawMap(std::vector<std::vector<int>> map, sf::RenderWindow& window) {
//    for (int x = 0; x < NUM_TILES_X; x++) {
//        for (int y = 0; y < NUM_TILES_Y; y++) {
//            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
//            if (map[x][y] == 1) {
//                tile.setFillColor(sf::Color::White);
//            }
//            else {
//                tile.setFillColor(sf::Color::Black);
//            }
//            tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
//            window.draw(tile);
//        }
//    }
//}

// Define main function
int main() {
    // Create the SFML window and set the view
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dungeon Crawler");
    sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(view);

    sf::Clock deltaClock;

    // Generate the rooms and create the map
    //std::vector<Room> rooms = generateRooms();
    //std::vector<std::vector<int>> map = createMap(rooms);

    sf::Texture fantasyTileTexture;

    // Load the tileset texture
    if (!fantasyTileTexture.loadFromFile("Oryx/oryx_16bit_fantasy_world_trans.png")) {
        std::cerr << "Failed to load tileset: " << "Oryx/oryx_16bit_fantasy_world_trans.png" << std::endl;
        // Error handling
    }

    // Create the player and set their starting position
    std::vector<std::vector<Room>> allRooms;

    RoomManager gameRooms(2, 2, NUM_TILES_X, NUM_TILES_Y, TILE_SIZE, fantasyTileTexture);

    auto player = std::make_shared<Player>(200, 200, 100, TILE_SIZE, "Oryx/oryx_16bit_fantasy_creatures_trans.png", gameRooms.getPlayerRoom());

    //Camera camera(window);

    //camera.setRoomView(*(gameRooms.getPlayerRoom()), TILE_SIZE);

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

            /*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                if (roomX + 1 < 3) {
                    roomX++;
                    currentRoom = allRooms[roomX][roomY];
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                if (roomX - 1 >= 0) {
                    roomX--;
                    currentRoom = allRooms[roomX][roomY];
                }
            }if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                if (roomY + 1 < 3) {
                    roomY++;
                    currentRoom = allRooms[roomX][roomY];
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                if (roomY - 1 >= 0) {
                    roomY--;
                    currentRoom = allRooms[roomX][roomY];
                }
            }
            */
        }

        // Calculate delta time
        sf::Time deltaTime = deltaClock.restart();

        // Check for collisions with rooms
        //for (int i = 0; i < rooms.size(); i++) {
        //    if (player.getX() >= rooms[i].x && player.getX() < rooms[i].x + rooms[i].width &&
        //        player.getY() >= rooms[i].y && player.getY() < rooms[i].y + rooms[i].height) {
        //        // TODO: Enter room
        //    }
        //}

        // Update player
        player->update(gameRooms.getPlayerRoom(), deltaTime, evnt);

        // Clear the window and draw the map and player
        window.clear();
        gameRooms.draw(window);
        player->draw(window, gameRooms.getPlayerRoom());
        window.display();
    }

    return 0;
}
