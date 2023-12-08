#include "Scene_Play.hpp"
#include "../GameEngine.hpp"

Scene_Play::Scene_Play(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

sf::Vector2f Scene_Play::gridToMidPixel(float gridX, float gridY, sf::IntRect& entityRect, sf::Vector2f& scale)
{
	auto posX = gridX * entityRect.getSize().x * scale.x;
	auto posY = gridY * entityRect.getSize().y * scale.y;
	auto midX = posX + entityRect.getSize().x * scale.x / 2.f;
	auto midY = posY + entityRect.getSize().y * scale.y / 2.f;

	return sf::Vector2f(midX, midY);
}

sf::Vector2i Scene_Play::pixelToGrid(sf::Vector2f& pos)
{
	// TODO: map pixel to grid
	auto tilePositionX = static_cast<int>(std::trunc(pos.x / gameTileSizeX));
	auto tilePositionY = static_cast<int>(std::trunc(pos.y / gameTileSizeY));
	return sf::Vector2i(tilePositionX, tilePositionY);
}

void Scene_Play::init()
{
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");		// Toggle drawing (T)extures
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");	// Toggle drawing (C)ollision Boxes
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");			// Toggle drawing (G)rid
	registerAction(sf::Keyboard::P, "EXPORT");

	registerAction(sf::Keyboard::W, "MOVE_UP");
	registerAction(sf::Keyboard::S, "MOVE_DOWN");
	registerAction(sf::Keyboard::A, "MOVE_LEFT");
	registerAction(sf::Keyboard::D, "MOVE_RIGHT");

	auto& gridFont = m_game->getAssets().getFont("arial");
	m_gridText.setFont(gridFont);
	m_gridText.setFillColor(sf::Color::Black);
	m_gridText.setCharacterSize(12);

	std::string levelPath = "../../../../data/saves/level1.json";

	loadTextureRects(levelPath);

	loadLevel(levelPath);

	m_systems = Systems(m_game, m_gridText);
}

void Scene_Play::loadLevel(std::string& filePath)
{
	//loadTextureRects(filePath);

	loadEntities(filePath);
}

void Scene_Play::loadTextureRects(std::string& filePath)
{
	std::ifstream input(filePath);
	if (!input.is_open())
	{
		std::cout << "Failed to open the file.\n";
	}
	json jsonData;
	input >> jsonData;
	input.close();

	std::cout << jsonData["textures"] << "\n";

	if (jsonData.contains("textures") && jsonData["textures"].is_array())
	{
		for (const auto& texture : jsonData["textures"])
		{
			const auto& textureName = texture["texture"];
			const auto& textureRects = texture["textureRects"];

			std::cout << "Loading texture named : " << textureName << "\n";

			if (textureRects.is_array())
			{

				for (const auto& textureRect : textureRects)
				{
					std::cout << "Loading texture rect named : " << textureRect["name"] << "\n";
					std::map<std::string, sf::IntRect> intRectMap;
					intRectMap[textureRect["name"]] = sf::IntRect(
						static_cast<int>(textureRect["x"].get<int>() * textureTileSizeX),
						static_cast<int>(textureRect["y"].get<int>() * textureTileSizeY),
						static_cast<int>(textureRect["width"].get<int>()),
						static_cast<int>(textureRect["height"].get<int>())
					);

					m_textureRectMap[textureName][textureRect["name"]] = intRectMap[textureRect["name"]];
				}
			}
		}
	}
}

void Scene_Play::loadEntities(std::string& filePath)
{
	// TODO: 
	// Read json file contents
	json jsonData = getJsonContents(filePath);

	// TODO: create some basic entities to render to the screen for now
	m_reg.clear();
	
	if (jsonData.contains("entities") && jsonData["entities"].is_array())
	{
		for (const auto& entity : jsonData["entities"])
		{
			std::string name = entity["type"].get<std::string>();
			std::string textureKey = entity["texture"].get<std::string>();
			const auto& posX = static_cast<float>(entity["x"].get<float>());
			const auto& posY = static_cast<float>(entity["y"].get<float>());
			sf::Sprite sprite;
			const auto& texture = m_game->getAssets().getTexture(textureKey);
			sprite.setTexture(texture);
			auto& textureRect = m_textureRectMap[textureKey][name];
			sf::Vector2f spritePos = { 
				posX,
				posY
			};
			sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };
			auto midPixelPos = gridToMidPixel(spritePos.x, spritePos.y, textureRect, scale);

			if (name.rfind("player", 0) == 0)
			{
				const auto player = makePlayer(
					m_reg,
					sprite,
					textureRect,
					midPixelPos,
					name,
					textureKey
				);
			}

			// Check if the start of the entity name starts with 'floor'
			if (name.rfind("floor", 0) == 0)
			{
				const auto floorEntity = makeFloor(
					m_reg,
					sprite,
					textureRect,
					midPixelPos,
					name,
					textureKey
				);
			}

			if (name.rfind("wall", 0) == 0)
			{
				const auto tileEntity = makeTile(
					m_reg,
					sprite,
					textureRect,
					midPixelPos,
					name,
					textureKey
				);
			}
		}
	}

	auto view = m_reg.view<CName, CPosition, CTile, CSprite, CScale>();

	/*for (const auto& e : view)
	{
		auto& name = view.get<CName>(e).name;
		auto& pos = view.get<CPosition>(e).pos;
		std::cout << "Entity " << name << " at position ( " << pos.x << ", " << pos.y << " )\n";
	}*/
	
	// Look for entities
	// Iterate through entities
	// create them based on their parameters
}

void Scene_Play::exportLevelToJson(std::string& filePath)
{
	json levelData;

	// Populate the JSON object with your data
	levelData["width"] = 24;
	levelData["height"] = 24;

	// Example entities array
	json entities = json::array();

	auto allView = m_reg.view<CPosition, CName, CSprite>();
	for (const auto& entity : allView)
	{
		auto& pos = allView.get<CPosition>(entity).pos;
		auto& name = allView.get<CName>(entity).name;
		auto& sprite = allView.get<CSprite>(entity).id;
		auto& textureName = allView.get<CSprite>(entity).textureName;;
		auto gridPos = pixelToGrid(pos);
		entities.push_back(
			{ 
				{"type", name},
				{"texture", textureName},
				{"x", gridPos.x}, 
				{"y", gridPos.y} 
			}
		);
	}
	levelData["entities"] = entities;

	json textures = json::array();

	// Loop through all textures and associated texture rects to save in your level
	for (const auto& [textureName, textureRectMap] : m_textureRectMap)
	{
		json textureRectArray = json::array();

		for (const auto& [textureRectName, textureIntRect] : textureRectMap)
		{
			textureRectArray.push_back(
				{
					{ "name", textureRectName },
					{ "x",		static_cast<int>(textureIntRect.left / textureTileSizeX) },
					{ "y",		static_cast<int>(textureIntRect.top / textureTileSizeY) },
					{ "width",	static_cast<int>(textureIntRect.width) },
					{ "height", static_cast<int>(textureIntRect.height) }
				}
			);
		}

		textures.push_back(
			{
				{"texture", textureName},
				{"textureRects", textureRectArray}
			}
		);
	}

	levelData["textures"] = textures;

	// Convert JSON object to string for writing to a file
	std::string jsonString = levelData.dump(4); // Use pretty printing with an indentation of 4 spaces

	// Print the JSON string
	// std::cout << jsonString << "\n";

	// Write JSON string to a file
	std::ofstream outputFile(filePath);
	outputFile << jsonString;
	outputFile.close();

	std::cout << "Exporting entities to json\n";
}

json Scene_Play::getJsonContents(std::string& filePath)
{
	std::ifstream input(filePath);
	if (!input.is_open())
	{
		std::cout << "Failed to open the file.\n";
	}
	json jsonData;
	input >> jsonData;
	input.close();
	return jsonData;
}

void Scene_Play::update()
{
	// color the background darker so you know that the game is paused
	/*if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }*/

	// Use the systems member of the scene to handle all system updates
	// on entities
	m_systems.update(m_reg, m_drawGrid, m_gridText);
}

void Scene_Play::onEnd()
{
	// These actions are here to stop the player from continuously moving
	// when holding a movement key down and exiting the play scene
	sDoAction(Action("MOVE_LEFT", "END"));
	sDoAction(Action("MOVE_RIGHT", "END"));
	sDoAction(Action("MOVE_DOWN", "END"));
	sDoAction(Action("MOVE_UP", "END"));

	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.type() == "START") 
	{
		if (action.name() == "TOGGLE_GRID")
		{
			m_drawGrid = !m_drawGrid;
		}

		if (action.name() == "MOVE_LEFT")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.left = true;
			}
		}

		if (action.name() == "MOVE_RIGHT")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.right = true;
			}
		}

		if (action.name() == "MOVE_UP")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.up = true;
			}
		}

		if (action.name() == "MOVE_DOWN")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.down = true;
			}
		}
	}
	
	if (action.type() == "END")
	{
		if (action.name() == "EXPORT")
		{
			std::string levelPath = "../../../../data/saves/level1.json";
			exportLevelToJson(levelPath);
		}

		if (action.name() == "MOVE_LEFT")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.left = false;
			}
		}

		if (action.name() == "MOVE_RIGHT")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.right = false;
			}
		}

		if (action.name() == "MOVE_UP")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.up = false;
			}
		}

		if (action.name() == "MOVE_DOWN")
		{
			const auto& playerView = m_reg.view<CInput, CPlayer>();
			for (const auto& entity : playerView)
			{
				auto& input = playerView.get<CInput>(entity);
				input.down = false;
			}
		}

		if (action.name() == "QUIT")
		{
			onEnd();
		}
	}
}

void Scene_Play::sRender()
{
}
