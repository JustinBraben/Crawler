#include "sMovement.hpp"
#include <entt/entity/registry.hpp>

void sMovement(entt::registry& reg)
{
	const auto view = reg.view<CInput, CPosition, CVelocity>();
	for (const auto& entity : view)
	{
		auto& input = view.get<CInput>(entity);
	}
}