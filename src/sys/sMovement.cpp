#include "sMovement.hpp"
#include <entt/entity/registry.hpp>

void sMovement(entt::registry& reg)
{
	const auto view = reg.view<CInput, CPosition, CVelocity>();
	for (const auto& entity : view)
	{
		auto& input = view.get<CInput>(entity);
		auto& velocity = view.get<CVelocity>(entity);
		auto& pos = view.get<CPosition>(entity);

		if (input.up)
		{
			velocity.vel.y += -playerAccelerationY;
			velocity.vel.y = std::clamp(velocity.vel.y, playerMinVelocityY, 0.f);
		}
		else if (!input.up && velocity.vel.y < 0)
		{
			velocity.vel.y += playerAccelerationY;
			velocity.vel.y = std::clamp(velocity.vel.y, playerMinVelocityY, 0.f);
		}

		if (input.down)
		{
			velocity.vel.y += playerAccelerationY;
			velocity.vel.y = std::clamp(velocity.vel.y, 0.f, playerMaxVelocityY);
		}
		else if (velocity.vel.y > 0)
		{
			velocity.vel.y += -playerAccelerationY;
			velocity.vel.y = std::clamp(velocity.vel.y, 0.f, playerMaxVelocityY);
		}

		if (input.left)
		{
			velocity.vel.x += -playerAccelerationX;
			velocity.vel.x = std::clamp(velocity.vel.x, playerMinVelocityX, 0.f);
		}
		else if (velocity.vel.x < 0)
		{
			velocity.vel.x += playerAccelerationY;
			velocity.vel.x = std::clamp(velocity.vel.x, playerMinVelocityX, 0.f);
		}

		if (input.right)
		{
			velocity.vel.x += playerAccelerationY;
			velocity.vel.x = std::clamp(velocity.vel.x, 0.f, playerMaxVelocityX);
		}
		else if (velocity.vel.x > 0)
		{
			velocity.vel.x += -playerAccelerationY;
			velocity.vel.x = std::clamp(velocity.vel.x, 0.f, playerMaxVelocityX);
		}

		pos.prevPos.x = pos.pos.x;
		pos.prevPos.y = pos.pos.y;

		pos.pos.x += velocity.vel.x;
		pos.pos.y += velocity.vel.y;
	}
}