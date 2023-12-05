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
	reg.emplace<CPosition>(player, sf::Vector2f(100, 100));
	reg.emplace<CVelocity>(player, velocity);
	reg.emplace<CBoundingBox>(player, size, halfSize);
	reg.emplace<CSprite>(player, sprite);
	reg.emplace<CScale>(player, scale);

	return player;
}
