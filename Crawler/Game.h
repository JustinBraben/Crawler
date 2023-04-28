#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "RoomManager.h"
#include "Player.h"
#include "Camera.h"
#include "GameState.h"

class Game
{
public:
	Game() {

	}

	void run() {
        //auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Dungeon Crawler");
        //window->setFramerateLimit(60);

        //// Initialize the menu state
        //std::shared_ptr<GameState> menuState = std::make_shared<MenuState>(window);
        //menuState->init();
        //pushState(menuState);

        //// Main loop
        //sf::Clock clock;
        //while (window->isOpen()) {
        //    sf::Event event;
        //    while (window->pollEvent(event)) {
        //        if (event.type == sf::Event::Closed) {
        //            window->close();
        //        }
        //        else {
        //            // Pass the event to the current state's event handler
        //            states.top()->handleInput(event);
        //        }
        //    }

        //    // Update the current state
        //    float dt = clock.restart().asSeconds();
        //    states.top()->update(dt);

        //    // Draw the current state
        //    window->clear();
        //    states.top()->render();
        //    window->display();
        //}
	}

	void update() {

	}
private:
	sf::RenderWindow m_window;
	std::stack<std::unique_ptr<GameState>> m_states;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<RoomManager> m_roomManager;
	std::shared_ptr<Camera> m_camera;
};

