#include "Factories.hpp"

entt::entity makePlayer(entt::registry &reg, sf::Sprite &sprite, sf::IntRect& textureRect, sf::Vector2f& pos)
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
	reg.emplace<CPosition>(player, pos);
	reg.emplace<CVelocity>(player, velocity);
	reg.emplace<CBoundingBox>(player, size, halfSize);
	reg.emplace<CSprite>(player, sprite, textureRect);
	reg.emplace<CScale>(player, scale);

	return player;
}

entt::entity makePlayer(entt::registry& reg, sf::Sprite& sprite, sf::IntRect& textureRect, sf::Vector2f& pos, std::string& name, std::string& textureName)
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

	const entt::entity entity = reg.create();
	reg.emplace<CPlayer>(entity);
	reg.emplace<CInput>(entity);
	reg.emplace<CName>(entity, name);
	reg.emplace<CVelocity>(entity);
	reg.emplace<CTile>(entity);
	reg.emplace<CPosition>(entity, pos);
	reg.emplace<CBoundingBox>(entity, size, halfSize);
	reg.emplace<CSprite>(entity, sprite, textureRect, textureName);
	reg.emplace<CScale>(entity, scale);

	return entity;
}


entt::entity makeTile(
	entt::registry& reg, 
	sf::Sprite& sprite, 
	sf::IntRect& textureRect, 
	sf::Vector2f& pos, 
	std::string& name, 
	std::string& textureName
)
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
	reg.emplace<CName>(tile, name);
	reg.emplace<CTile>(tile);
	reg.emplace<CPosition>(tile, pos);
	reg.emplace<CBoundingBox>(tile, size, halfSize);
	reg.emplace<CSprite>(tile, sprite, textureRect, textureName);
	reg.emplace<CScale>(tile, scale);

	return tile;
}

entt::entity makeFloor(
	entt::registry& reg, 
	sf::Sprite& sprite, 
	sf::IntRect& textureRect, 
	sf::Vector2f& pos, 
	std::string& name, 
	std::string& textureName
)
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

	const entt::entity floor = reg.create();
	reg.emplace<CName>(floor, name);
	reg.emplace<CPosition>(floor, pos);
	reg.emplace<CTile>(floor);
	reg.emplace<CSprite>(floor, sprite, textureRect, textureName);
	reg.emplace<CScale>(floor, scale);

	return floor;
}

void makeRoom(entt::registry& reg, sf::Sprite& sprite, sf::Vector2f& startingPos)
{
	// TODO: Create a room of entities
}
