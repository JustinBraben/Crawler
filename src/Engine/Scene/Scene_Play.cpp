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
	auto tilePositionX = static_cast<int>(std::floor(pos.x / gameTileSizeX));
	auto tilePositionY = static_cast<int>(std::trunc(pos.y / gameTileSizeY));
	return sf::Vector2i(tilePositionX, tilePositionY);
}

void Scene_Play::init()
{
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::P, "EXPORT");

	registerAction(sf::Keyboard::W, "MOVE_UP");
	registerAction(sf::Keyboard::S, "MOVE_DOWN");
	registerAction(sf::Keyboard::A, "MOVE_LEFT");
	registerAction(sf::Keyboard::D, "MOVE_RIGHT");

	std::string levelPath = "../../../../data/saves/level1.json";

	loadTextureRects(levelPath);

	//createLevel();

	loadLevel(levelPath);
}

void Scene_Play::createLevel()
{
	// TODO: create some basic entities to render to the screen for now
	m_reg.clear();

	sf::Sprite playerSprite;
	auto& playerTexture = m_game->getAssets().getTexture("players blue x1");
	playerSprite.setTexture(playerTexture);
	sf::IntRect playerRect = { 0, 0, 32, 32 };
	sf::Vector2f playerPos = { 3.f, 3.f };
	sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };
	auto midPixelPlayerPos = gridToMidPixel(playerPos.x, playerPos.y, playerRect, scale);

	const auto playerEntity = makePlayer(
		m_reg, 
		std::move(playerSprite), 
		playerRect, 
		midPixelPlayerPos
	);

	/*for (float i = 0; i < 4; i++)
	{
		for (float j = 0; j < 4; j++)
		{
			sf::Sprite tileSprite;
			const std::string textureKey = "tileset x1";
			auto& tileTexture = m_game->getAssets().getTexture(textureKey);
			tileSprite.setTexture(tileTexture);
			sf::IntRect tileRect = { 5 * 32, 0 * 32, 32, 32 };
			sf::Vector2f tilePos = { i * 1, j * 1 };
			sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };
			auto midPixelPos = gridToMidPixel(tilePos.x, tilePos.y, tileRect, scale);

			const auto tileEntity = makeTile(
				m_reg,
				tileSprite,
				tileRect,
				midPixelPos
			);
		}
	}*/

	for (float i = 4; i < 8; i++)
	{
		for (float j = 4; j < 8; j++)
		{
			std::string floorType = "floor1";
			std::string textureKey = "tileset x1";
			sf::Sprite floorSprite;
			const auto& floorTexture = m_game->getAssets().getTexture(textureKey);
			floorSprite.setTexture(floorTexture);
			sf::IntRect floorRect = { 34 * 32, 1 * 32, 32, 32 };
			sf::Vector2f floorPos = { i * 1, j * 1 };
			sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };
			auto midPixelPos = gridToMidPixel(floorPos.x, floorPos.y, floorRect, scale);

			std::cout << "midPixelPos is ( " << midPixelPos.x << ", " << midPixelPos.y << " )\n";

			const auto floorEntity = makeFloor(
				m_reg,
				floorSprite,
				floorRect,
				midPixelPos,
				floorType,
				textureKey
			);
		}
	}

	std::cout << "Created Level with new Player \n";

	/*std::ifstream input("../../../../data/saves/level1.json");
	json data = json::parse(input);
	std::cout << "Reading json data\n";
	std::cout << "width is : " << data["width"] << "\n";
	std::cout << "height is : " << data["height"] << "\n";
	std::cout << "entities is : " << data["entities"] << "\n";*/
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

	auto allView = m_reg.view<CPosition, CTile, CName, CSprite>();
	for (const auto& entity : allView)
	{
		auto& pos = allView.get<CPosition>(entity).pos;
		auto& name = allView.get<CName>(entity).name;
		auto& sprite = allView.get<CSprite>(entity).id;
		auto gridPos = pixelToGrid(pos);
		entities.push_back(
			{ 
				{"type", name},
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
					{ "x",		static_cast<int>(textureIntRect.left / gameTileSizeX) },
					{ "y",		static_cast<int>(textureIntRect.top / gameTileSizeY) },
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

void Scene_Play::playerRender()
{
	const auto playerView = m_reg.view<CPlayer, CBoundingBox, CPosition, CVelocity, CScale, CSprite>();

	for (const auto& player : playerView)
	{
		auto& pos = playerView.get<CPosition>(player).pos;
		auto& box = playerView.get<CBoundingBox>(player);
		auto& velocity = playerView.get<CVelocity>(player).vel;
		auto& scale = playerView.get<CScale>(player).scale;
		auto& sprite = playerView.get<CSprite>(player).id;
		auto& texRect = playerView.get<CSprite>(player).texRect;
		sprite.setTextureRect(texRect);
		sprite.setOrigin(box.halfSize);
		sprite.setScale(scale);
		sprite.setPosition(pos);
		m_game->window().draw(sprite);
	}
}

void Scene_Play::tileRender()
{
	const auto tileView = m_reg.view<CTile, CBoundingBox, CPosition, CScale, CSprite>();

	for (const auto& tile : tileView)
	{
		auto& pos = tileView.get<CPosition>(tile).pos;
		auto& box = tileView.get<CBoundingBox>(tile);
		auto& scale = tileView.get<CScale>(tile).scale;
		auto& sprite = tileView.get<CSprite>(tile).id;
		auto& texRect = tileView.get<CSprite>(tile).texRect;
		sprite.setTextureRect(texRect);
		sprite.setOrigin(box.halfSize);
		sprite.setScale(scale);
		sprite.setPosition(pos);
		m_game->window().draw(sprite);
	}
}

void Scene_Play::floorRender()
{
	const auto floorView = m_reg.view<CTile, CName, CPosition, CScale, CSprite>();

	for (const auto& tile : floorView)
	{
		auto& pos = floorView.get<CPosition>(tile).pos;
		auto& scale = floorView.get<CScale>(tile).scale;
		auto& sprite = floorView.get<CSprite>(tile).id;
		auto& texRect = floorView.get<CSprite>(tile).texRect;
		auto& name = floorView.get<CName>(tile).name;
		sprite.setTextureRect(texRect);
		sprite.setOrigin(
			sf::Vector2f(
				sprite.getTextureRect().getSize().x / 2.f, 
				sprite.getTextureRect().getSize().y / 2.f
			)
		);
		sprite.setScale(scale);
		sprite.setPosition(pos);
		m_game->window().draw(sprite);

		/*std::cout 
			<< "Entity " << name 
			<< " with textureName " << floorView.get<CSprite>(tile).textureName
			<< " at position ( " << pos.x << ", " << pos.y << " )\n";*/
	}
}

void Scene_Play::update()
{
	sRender();
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

	}
	
	if (action.type() == "END")
	{
		if (action.name() == "EXPORT")
		{
			std::string levelPath = "../../../../data/saves/level1.json";
			exportLevelToJson(levelPath);
		}
		if (action.name() == "QUIT")
		{
			onEnd();
		}
	}
}

void Scene_Play::sRender()
{
	// color the background darker so you know that the game is paused
	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	floorRender();

	tileRender();

	playerRender();

	m_game->window().display();
}
