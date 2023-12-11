#include "sRender.hpp"
#include <entt/entity/registry.hpp>

#include "../Engine/GameEngine.hpp"

void sRender(entt::registry& reg, GameEngine* gameEngine, bool drawGrid, sf::Text& gridText)
{
	gameEngine->window().clear(sf::Color(100, 100, 255));

	sCamera(reg, gameEngine);

	sFloorRender(reg, gameEngine);

	sWallRender(reg, gameEngine);

	sPlayerRender(reg, gameEngine);

	if (drawGrid)
	{
		sGridRender(reg, gameEngine, gridText);
	}

	gameEngine->window().display();
}

void sFloorRender(entt::registry& reg, GameEngine* gameEngine)
{
	const auto floorView = reg.view<CTile, CName, CPosition, CScale, CSprite>();

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
		gameEngine->window().draw(sprite);

		/*std::cout
			<< "Entity " << name
			<< " with textureName " << floorView.get<CSprite>(tile).textureName
			<< " at position ( " << pos.x << ", " << pos.y << " )\n";*/
	}
}

void sWallRender(entt::registry& reg, GameEngine* gameEngine)
{
	const auto tileView = reg.view<CName, CBoundingBox, CPosition, CScale, CSprite>();

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
		gameEngine->window().draw(sprite);
	}
}

void sPlayerRender(entt::registry& reg, GameEngine* gameEngine)
{
	const auto playerView = reg.view<CPlayer, CBoundingBox, CPosition, CVelocity, CScale, CSprite>();

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
		gameEngine->window().draw(sprite);
	}
}

void sGridRender(entt::registry& reg, GameEngine* gameEngine, sf::Text& gridText)
{
	auto currentView = gameEngine->window().getView();

	auto cameraLeft = currentView.getCenter().x - width / 2.f;
	auto cameraTop = currentView.getCenter().y - height / 2.f;

	auto cameraRight = cameraLeft + width;
	auto cameraBottom = cameraTop + height;

	sf::Vector2f gridStart = { cameraLeft, cameraTop };

	auto startGridPos = pixelToGrid(gridStart);

	for (float x = static_cast<float>(startGridPos.x * gameTileSizeX); x < cameraRight; x += gameTileSizeX)
	{
		drawLine(sf::Vector2f(x, cameraBottom), sf::Vector2f(x, cameraTop), gameEngine);
	}

	for (float y = static_cast<float>(startGridPos.y * gameTileSizeY); y < cameraBottom; y += gameTileSizeY)
	{
		drawLine(sf::Vector2f(cameraLeft, y), sf::Vector2f(cameraRight, y), gameEngine);
		for (float x = static_cast<float>(startGridPos.x * gameTileSizeX); x < cameraRight; x += gameTileSizeX)
		{
			sf::Vector2f curPos = { x, y };
			const auto& gridPos = pixelToGrid(curPos);
			std::string xCell = std::to_string(static_cast<int>(gridPos.x));
			std::string yCell = std::to_string(static_cast<int>(gridPos.y));
			gridText.setString("(" + xCell + "," + yCell + ")");
			gridText.setPosition(x + 3, y + 2);
			gridText.setFillColor(sf::Color::White);
			gameEngine->window().draw(gridText);
		}
	}
}

void sCamera(entt::registry& reg, GameEngine* gameEngine)
{
	const auto playerView = reg.view<CPlayer, CBoundingBox, CPosition, CScale, CSprite>();

	for (const auto& player : playerView)
	{
		sf::View gameView = gameEngine->window().getView();

		auto cameraCenterX = gameView.getCenter().x;
		auto cameraCenterY = gameView.getCenter().y;

		auto cameraLeftX = gameView.getCenter().x - (static_cast<float>(gameEngine->window().getSize().x) / 2.f);
		auto cameraTopY = gameView.getCenter().y + (static_cast<float>(gameEngine->window().getSize().y) / 2.f);

		auto cameraRightX = cameraLeftX + gameEngine->window().getSize().x;
		auto cameraBottomY = cameraTopY - gameEngine->window().getSize().y;

		auto& pos = playerView.get<CPosition>(player).pos;

		// Define the speed at which the camera follows the player
		float followSpeed = 0.02f;

		// Use lerp to smoothly interpolate between the current camera position and the player position
		cameraCenterX = smoothCameraFollow(cameraCenterX, pos.x, followSpeed);
		cameraCenterY = smoothCameraFollow(cameraCenterY, pos.y, followSpeed);

		gameView.setCenter(cameraCenterX, cameraCenterY);
		gameEngine->window().setView(gameView);
	}
}

// Linear interpolation function
float smoothCameraFollow(float x, float y, float adjust)
{
	return (1 - adjust) * x + adjust * y;
}

sf::Vector2i pixelToGrid(sf::Vector2f& pos)
{
	// TODO: map pixel to grid
	auto tilePositionX = static_cast<int>(std::trunc(pos.x / gameTileSizeX));
	auto tilePositionY = static_cast<int>(std::trunc(pos.y / gameTileSizeY));
	return sf::Vector2i(tilePositionX, tilePositionY);
}

void drawLine(const sf::Vector2f& p1, const sf::Vector2f& p2, GameEngine* gameEngine)
{
	sf::VertexArray line(sf::Lines, 2);

	line[0].position = sf::Vector2f(p1.x, p1.y); // Set the position of the first vertex
	line[0].color = sf::Color::White; // Set the color of the first vertex

	line[1].position = sf::Vector2f(p2.x, p2.y); // Set the position of the second vertex
	line[1].color = sf::Color::White; // Set the color of the second vertex

	gameEngine->window().draw(line);
}