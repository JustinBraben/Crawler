#ifndef SCENE_MENU_HPP
#define SCENE_MENU_HPP

#include "Scene.hpp"
#include <map>
#include <memory>
#include <deque>
#include <filesystem>

#include <entt/entity/registry.hpp>
#include <SFML/Graphics.hpp>

class Scene_Menu : public Scene
{
protected:

	std::string m_title;
	std::vector<std::string> m_menuStrings;
	sf::Text m_menuText;
	size_t m_selectedMenuIndex = 0;

	void init();
	void loadMenuPaths(const std::filesystem::path& folderPath);

public:
	void onEnd() override;
	void update() override;
	void sDoAction(const Action& action) override;
	void sRender() override;

	Scene_Menu(GameEngine* gameEngine = nullptr);

private:
};

#endif // SCENE_MENU_HPP