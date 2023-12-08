#include "sAnimation.hpp"
#include <entt/entity/registry.hpp>

void sAnimation(entt::registry& reg)
{
	const auto view = reg.view<CInput, CScale>();
	for (const auto& entity : view)
	{
		auto& input = view.get<CInput>(entity);
		auto& scale = view.get<CScale>(entity);

		if (input.left)
		{
			scale.scale.x = -1.f * std::abs(scale.scale.x);
		}

		if (input.right)
		{
			scale.scale.x = std::abs(scale.scale.x);
		}
	}
}
