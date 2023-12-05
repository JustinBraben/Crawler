#include "Assets.hpp"

#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>
#include <iostream>

class GameEngine {
protected:
	sf::RenderWindow m_window;
	Assets m_assets;
	bool m_running = true;

	void init();

public:
	GameEngine();

	void quit();
	void run();
};