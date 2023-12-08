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

void Systems::update(entt::registry& reg)
{
	sMovement(reg);
	sAnimation(reg);
}