#pragma once

#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>

class Game {
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;

	std::shared_ptr<Entity> m_player;

	void init(const std::string& config);	// initialize the GameState with a config file path
	void setPaused(bool paused);			// pause the game

	void spawnPlayer();
	void spawnEnemy();

public:
	Game(const std::string& configPath);

	void run();
};