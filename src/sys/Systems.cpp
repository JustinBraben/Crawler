#include "Systems.hpp"
#include "sMovement.hpp"
#include <entt/entity/registry.hpp>

Systems::Systems()
{
}

void Systems::update(entt::registry& reg)
{
	sMovement(reg);
}