#pragma once
#include "Player.h"
#include "RoomManager.h"
class CollisionManager {
public:
    // Constructor: takes references to the Player and RoomManager
    CollisionManager(std::shared_ptr<Player> player, std::shared_ptr <RoomManager> roomManager)
        : player_(player), roomManager_(roomManager) {}

    // Check and resolve collisions for the player
    void checkPlayerCollisions() {
        //// Get the player's current position and future position after movement
        auto currentPlayerPosition = player_->getPlayerTopLeft();
        auto futurePlayerPosition = player_->getFuturePosition();

        // Get the current room from the RoomManager
        auto currentRoom = roomManager_->getPlayerRoom();

        // Check for collisions with walls
        if (checkCollision(futurePlayerPosition, currentRoom, TileType::Wall)) {
            //// Resolve wall collision: do not allow the player to move
            //player_.cancelMovement();
        }
        else {
            // No wall collision, check for collisions with doors
            // checkCollision(futurePlayerPosition, currentRoom, TileType::Door)
            auto collidingDoor = getCollisionDoor(futurePlayerPosition, currentRoom);
            if (collidingDoor != nullptr) {
                // Resolve door collision: teleport the player to the linked room and position
                roomManager_->setCurrentRoom(collidingDoor->linkedRoomId);
                player_->setPosition(static_cast<float>(collidingDoor->linkedPosition.x * roomManager_->getPlayerRoom()->getTileSize()),
                    static_cast<float>(collidingDoor->linkedPosition.y * roomManager_->getPlayerRoom()->getTileSize()));
            }
        }

    }

    bool checkCollision(sf::Vector2f futurePosition, std::shared_ptr<Room> room, TileType checkTileType, int radius = 1) {
        auto& tileSet = room->getTiles();
        sf::Vector2i playerTile = player_->getPlayerTile();
        sf::Vector2f vec2fTileSize(room->getTileSize(), room->getTileSize());
        sf::FloatRect nextHitbox(futurePosition, vec2fTileSize);

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int checkX = playerTile.x + i;
                int checkY = playerTile.y + j;
                if (checkX >= 0 && checkX < tileSet.size() && checkY >= 0 && checkY < tileSet[checkX].size()) {
                    auto tile = tileSet[checkX][checkY];
                    if (tile->getType() == checkTileType) {
                        sf::FloatRect tileHitbox = tile->getTileHitBox();
                        if (nextHitbox.intersects(tileHitbox)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    std::shared_ptr<Door> getCollisionDoor(sf::Vector2f futurePosition, std::shared_ptr<Room> room, int radius = 1) {
        auto& tileSet = room->getTiles();
        sf::Vector2i playerTile = player_->getPlayerTile();
        sf::Vector2f vec2fTileSize(room->getTileSize(), room->getTileSize());
        sf::FloatRect nextHitbox(futurePosition, vec2fTileSize);

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int checkX = playerTile.x + i;
                int checkY = playerTile.y + j;
                if (checkX >= 0 && checkX < tileSet.size() && checkY >= 0 && checkY < tileSet[checkX].size()) {
                    auto tile = tileSet[checkX][checkY];
                    if (tile->getType() == TileType::Door) {
                        sf::FloatRect tileHitbox = tile->getTileHitBox();
                        if (nextHitbox.intersects(tileHitbox)) {
                            auto tilePos = tile->getTopLeft();
                            auto tilePosTransformed = sf::Vector2i(static_cast<int>(tilePos.x) / room->getTileSize(),
                                static_cast<int>(tilePos.y) / room->getTileSize());
                            // find door with position tilePos
                            auto targetDoor = findDoorByPosition(room->getDoors(), tilePosTransformed);
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    std::shared_ptr<Door> findDoorByPosition(const std::vector<std::shared_ptr<Door>>& doors, const sf::Vector2i& position) {
        auto it = std::find_if(doors.begin(), doors.end(), [&position](const std::shared_ptr<Door>& door) {
            return door->position == position;
            });

        if (it != doors.end()) {
            return *it;
        }
        else {
            return nullptr;
        }
    }

private:
    // Check if the player's future position collides with any walls in the room
    //bool isCollidingWithWalls(const Room& room, const sf::Vector2f& futurePlayerPosition) {
    //    // Check for wall collisions using the room's tiles
    //    // (Assuming you have a method to get the Tile at a specific position in the room)
    //    Tile& tile = room.getTileAt(futurePlayerPosition);
    //    return tile.getType() == TileType::Wall;
    //}

    // Check if the player's future position collides with any doors in the room
    // Returns a pointer to the colliding door or nullptr if there's no collision
    //Door* isCollidingWithDoors(std::shared_ptr<Room> room, sf::Vector2f& futurePlayerPosition) {
    //    // Iterate through the room's doors
    //    for (auto& door : room->getDoors()) {
    //        // Check for collision with the door using the door's position
    //        // (Assuming you have a method to check if two objects collide based on their positions)
    //        if (areObjectsColliding(player_, door)) {
    //            return door;
    //        }
    //    }
    //    return nullptr;
    //}
   

    // References to the Player and RoomManager
    std::shared_ptr<Player> player_;
    std::shared_ptr<RoomManager> roomManager_;
};

