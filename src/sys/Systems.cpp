#include "Systems.hpp"
#include <entt/entity/registry.hpp>

#include "../Engine/GameEngine.hpp"

Systems::Systems()
{
}

Systems::Systems(GameEngine* gameEngine)
	: m_game(gameEngine)
{
}

Systems::Systems(GameEngine* gameEngine, sf::Text& gridText)
	: m_game(gameEngine), m_gridText(gridText)
{
}

void Systems::update(entt::registry& reg, bool drawGrid, sf::Text& gridText)
{
	sMovement(reg);
	sAnimation(reg);
	sRender(reg, m_game, drawGrid, m_gridText);
}