#pragma once
#include <SFML/Graphics.hpp>
#include "Room.h"

class Camera{
public:
    // constructor and other public functions here
    Camera(sf::RenderWindow& window) {
        view.setSize(sf::Vector2f(window.getSize()));
        view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
        window.setView(view);
    }

    void setRoomView(std::shared_ptr<Room> room, int tileSize) {
        sf::Vector2f roomSize(room->getWidth() * tileSize, room->getHeight() * tileSize);
        sf::Vector2f roomPos(room->getX() * tileSize, room->getY() * tileSize);
        view.setSize(roomSize);
        view.setCenter(roomPos + roomSize / 2.f);
    }
private:
    sf::View view;
};

