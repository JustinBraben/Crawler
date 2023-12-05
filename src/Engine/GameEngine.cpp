#include "GameEngine.hpp"

GameEngine::GameEngine()
{
	init();
}

void GameEngine::init()
{
	// TODO: go through the assets folder
	// and add every texture to its own spot in the texture map
	std::filesystem::path assetsPath(assetsLoadPath);
	m_assets = Assets(assetsPath);

	m_window.create(sf::VideoMode(width, height), "Crawler");
	m_window.setFramerateLimit(144);

	changeScene("MENU", std::make_shared<Scene_Menu>(this));
}

void GameEngine::update()
{
	sUserInput();

	currentScene()->update();
}

void GameEngine::sUserInput()
{
	sf::Event evnt;
	while (m_window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed) {
			quit();
		}

		if (evnt.type == sf::Event::KeyPressed || evnt.type == sf::Event::KeyReleased)
		{
			auto scene = currentScene();

			// if the current scene does not have an action associated with this key, skip the event
			if (currentScene()->getActionMap().find(evnt.key.code) == currentScene()->getActionMap().end())
				continue;

			// determine start or end action by whether it was key press or release
			const std::string actionType = (evnt.type == sf::Event::KeyPressed) ? "START" : "END";

			// look up the action and send the action to the scene
			currentScene()->sDoAction(Action(currentScene()->getActionMap().at(evnt.key.code), actionType));
		}
	}
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_sceneMap[m_currentScene];
}

void GameEngine::quit()
{
	if (m_currentScene == "MENU") {
		m_running = false;
	}
}

void GameEngine::run()
{
	std::cout << "Game is now running\n";

	while (isRunning())
	{
		update();
	}

	m_window.close();

	std::cout << "Game is now done running, Press Enter to continue...\n";

	std::cin.get();     // Wait for the user to press Enter
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}

const Assets& GameEngine::getAssets() const
{
	return m_assets;
}

bool GameEngine::isRunning()
{
	return m_running && m_window.isOpen();
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	auto it = m_sceneMap.find(sceneName);

	if (it != m_sceneMap.end()) {
		// Scene already exists, set it as the current scene
		m_currentScene = sceneName;

		float windowCenterX = (this)->window().getSize().x / 2.0f;
		float windowCenterY = (this)->window().getSize().y / 2.0f;
		sf::View view = (this)->window().getView();
		view.setCenter(windowCenterX, windowCenterY);

		(this)->window().setView(view);

		// Optionally end the current scene if requested
		if (endCurrentScene)
		{
			// Call any necessary cleanup or end functions on the current scene
			// it->second->end();
		}
	}
	else {
		// Add the new scene to the map
		m_sceneMap[sceneName] = scene;
		m_currentScene = sceneName;
		//if (m_currentScene == "MENU") {
		//	// If its menu set delay to true 
		//	m_sceneMap[sceneName]->setDelayMove();
		//}
	}
}