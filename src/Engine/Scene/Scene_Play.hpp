#ifndef SCENE_PLAY_HPP
#define SCENE_PLAY_HPP

#include <fstream>
#include <iostream>
#include <filesystem>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Scene.hpp"

#include "../../Core/Factories.hpp"

#include "../../Sys/Systems.hpp"

#include "../Components/CAnimation.hpp"
#include "../Components/CBoundingBox.hpp"
#include "../Components/CEnemy.hpp"
#include "../Components/CInput.hpp"
#include "../Components/CName.hpp"
#include "../Components/CPlayer.hpp"
#include "../Components/CPosition.hpp"
#include "../Components/CScale.hpp"
#include "../Components/CSprite.hpp"
#include "../Components/CTile.hpp"
#include "../Components/CVelocity.hpp"

class Scene_Play : public Scene {
protected:
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;
	sf::Text m_gridText;
	std::map<std::string, std::map<std::string, sf::IntRect>> m_textureRectMap;
	Systems m_systems;

	void init();
	void init(const std::filesystem::path& filePath);

	void loadLevel(std::string& filePath);
	void loadLevel(const std::filesystem::path& filePath);
	void loadTextureRects(std::string& filePath);
	void loadTextureRects(const std::filesystem::path& filePath);
	void loadEntities(std::string& filePath);
	void loadEntities(const std::filesystem::path& filePath);
	void exportLevelToJson(std::string& filePath);
	json getJsonContents(std::string& filePath);

public:

	Scene_Play(GameEngine* gameEngine);
	Scene_Play(GameEngine* gameEngine, const std::filesystem::path& filePath);

	sf::Vector2f gridToMidPixel(float gridX, float gridY, sf::IntRect& entityRect, sf::Vector2f& scale);

	sf::Vector2i pixelToGrid(sf::Vector2f& pos);

	void update() override;
	void onEnd() override;
	void sDoAction(const Action& action) override;
	void sRender() override;
};

#endif // !SCENE_PLAY_HPP
