#ifndef SCENE_PLAY_HPP
#define SCENE_PLAY_HPP

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Scene.hpp"

#include "../../core/Factories.hpp"

#include "../Components/CBoundingBox.hpp"
#include "../Components/CPosition.hpp"
#include "../Components/CName.hpp"
#include "../Components/CScale.hpp"
#include "../Components/CSprite.hpp"
#include "../Components/CTile.hpp"
#include "../Components/CVelocity.hpp"

class Scene_Play : public Scene {
protected:
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;
	std::map<std::string, std::map<std::string, sf::IntRect>> m_textureRectMap;

	void init();

	void loadLevel(std::string& filePath);
	void loadTextureRects(std::string& filePath);
	void loadEntities(std::string& filePath);
	void exportLevelToJson(std::string& filePath);
	json getJsonContents(std::string& filePath);

	void playerRender();
	void tileRender();
	void floorRender();
public:

	Scene_Play(GameEngine* gameEngine);

	sf::Vector2f gridToMidPixel(float gridX, float gridY, sf::IntRect& entityRect, sf::Vector2f& scale);

	sf::Vector2i pixelToGrid(sf::Vector2f& pos);

	void update() override;
	void onEnd() override;
	void sDoAction(const Action& action) override;
	void sRender() override;
};

#endif // !SCENE_PLAY_HPP
