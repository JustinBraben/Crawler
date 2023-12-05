#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>
#include <iostream>

class GameEngine {
protected:
	sf::RenderWindow m_window;

	void init();

public:
	GameEngine();

	void quit();
	void run();
};