#include "Factories.hpp"

entt::entity makePlayer(entt::registry &reg, sf::Sprite &sprite, sf::IntRect& textureRect)
{

	sf::Vector2f size = sf::Vector2f(
		static_cast<float>(textureRect.getSize().x),
		static_cast<float>(textureRect.getSize().y)
	);

	sf::Vector2f halfSize = sf::Vector2f(
		static_cast<float>(textureRect.getSize().x / 2.f),
		static_cast<float>(textureRect.getSize().y / 2.f)
	);

	sf::Vector2f velocity = { 0.f, 0.f };

	sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };

	const entt::entity player = reg.create();
	reg.emplace<CPlayer>(player);
	reg.emplace<CPosition>(player, sf::Vector2f(200, 200));
	reg.emplace<CVelocity>(player, velocity);
	reg.emplace<CBoundingBox>(player, size, halfSize);
	reg.emplace<CSprite>(player, sprite, textureRect);
	reg.emplace<CScale>(player, scale);

	return player;
}

entt::entity makeTile(entt::registry& reg, sf::Sprite& sprite, sf::IntRect& textureRect, sf::Vector2f& pos)
{
	sf::Vector2f size = sf::Vector2f(
		static_cast<float>(textureRect.getSize().x),
		static_cast<float>(textureRect.getSize().y)
	);

	sf::Vector2f halfSize = sf::Vector2f(
		static_cast<float>(textureRect.getSize().x / 2.f),
		static_cast<float>(textureRect.getSize().y / 2.f)
	);

	sf::Vector2f scale = { gameTileSizeX / textureTileSizeX, gameTileSizeY / textureTileSizeY };

	const entt::entity tile = reg.create();
	reg.emplace<CTile>(tile);
	reg.emplace<CPosition>(tile, pos);
	reg.emplace<CBoundingBox>(tile, size, halfSize);
	reg.emplace<CSprite>(tile, sprite, textureRect);
	reg.emplace<CScale>(tile, scale);

	return tile;
}

void makeRoom(entt::registry& reg, sf::Sprite& sprite, sf::Vector2f& startingPos)
{
	// TODO: Create a room of entities
}
