#include "GameEngine.hpp"

GameEngine::GameEngine()
{
	init();
}

void GameEngine::init()
{
	// TODO: go through the assets folder
	// and add every texture to its own spot in the texture map
	std::filesystem::path assetsPath("../../../../assets");
	m_assets = Assets(assetsPath);

	m_window.create(sf::VideoMode(1280, 768), "Crawler");
	m_window.setFramerateLimit(144);
}

void GameEngine::run()
{
	std::cout << "Game is running\n";
}
