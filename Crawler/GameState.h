#pragma once
#include <SFML/Graphics.hpp>
class GameState {
public:
    GameState(std::shared_ptr<sf::RenderWindow> window) : m_window(window) {}
    virtual void init() = 0;
    virtual void handleInput(sf::Event event) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
protected:
    std::shared_ptr<sf::RenderWindow> m_window;
};

