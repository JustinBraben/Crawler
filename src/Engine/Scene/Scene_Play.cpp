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

	createLevel();
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
		playerSprite, 
		playerRect, 
		midPixelPlayerPos
	);

	for (float i = 0; i < 4; i++)
	{
		for (float j = 0; j < 4; j++)
		{
			sf::Sprite floorSprite;
			auto& floorTexture = m_game->getAssets().getTexture("tileset x1");
			floorSprite.setTexture(floorTexture);
			sf::IntRect floorRect = { 5 * 32, 0 * 32, 32, 32 };
			sf::Vector2f floorPos = { i * 1, j * 1 };
			sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };
			auto midPixelPos = gridToMidPixel(floorPos.x, floorPos.y, floorRect, scale);

			const auto floorEntity = makeTile(
				m_reg,
				floorSprite,
				floorRect,
				midPixelPos
			);
		}
	}

	for (float i = 4; i < 8; i++)
	{
		for (float j = 4; j < 8; j++)
		{
			sf::Sprite tileSprite;
			auto& tileTexture = m_game->getAssets().getTexture("tileset x1");
			tileSprite.setTexture(tileTexture);
			sf::IntRect tileRect = { 34 * 32, 1 * 32, 32, 32 };
			sf::Vector2f tilePos = { i * 1, j * 1 };
			sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };
			auto midPixelPos = gridToMidPixel(tilePos.x, tilePos.y, tileRect, scale);

			const auto tileEntity = makeFloor(
				m_reg,
				tileSprite,
				tileRect,
				midPixelPos
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
	const auto floorView = m_reg.view<CTile, CPosition, CScale, CSprite>();

	for (const auto& tile : floorView)
	{
		auto& pos = floorView.get<CPosition>(tile).pos;
		auto& scale = floorView.get<CScale>(tile).scale;
		auto& sprite = floorView.get<CSprite>(tile).id;
		auto& texRect = floorView.get<CSprite>(tile).texRect;
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

			json levelData;

			// Populate the JSON object with your data
			levelData["width"] = 24;
			levelData["height"] = 24;

			// Example entities array
			json entities = json::array();

			auto allView = m_reg.view<CPosition, CTile, CName>();
			for (const auto& entity : allView)
			{
				auto& pos = allView.get<CPosition>(entity).pos;
				auto& name = allView.get<CName>(entity).name;
				auto gridPos = pixelToGrid(pos);
				std::cout << "Entity at position ( " << pos.x << ", " << pos.y << " )\n";
				entities.push_back({ {"type", name}, {"x", gridPos.x}, {"y", gridPos.y} });
			}
			levelData["entities"] = entities;

			// Convert JSON object to string for writing to a file
			std::string jsonString = levelData.dump(4); // Use pretty printing with an indentation of 4 spaces

			// Print the JSON string
			std::cout << jsonString << "\n";

			// Write JSON string to a file
			std::ofstream outputFile("../../../../data/saves/level1.json");
			outputFile << jsonString;
			outputFile.close();

			std::cout << "Exporting entities to json\n";
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
