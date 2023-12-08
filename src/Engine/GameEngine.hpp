#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "Assets.hpp"
#include "Scene/Scene_Menu.hpp"

#include "../Configs/Constants.hpp"

#include <SFML/Graphics.hpp>
#include <entt/entity/registry.hpp>
#include <iostream>

using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;

class GameEngine 
{
protected:
	sf::RenderWindow m_window;
	Assets m_assets;
	std::string m_currentScene;
	SceneMap m_sceneMap;
	bool m_running = true;
	sf::View m_gameView;

	void init();
	void update();

	void sUserInput();

	std::shared_ptr<Scene> currentScene();

public:
	GameEngine();

	// change the current scene's string
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
	void setView(sf::View& view);

	void quit();
	void run();

	sf::RenderWindow& window();
	sf::View getView();
	const Assets& getAssets() const;
	bool isRunning();
};

#endif // !GAMEENGINE_HPP