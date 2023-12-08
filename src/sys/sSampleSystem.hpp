#ifndef SSAMPLESYSTEM_HPP
#define SSAMPLESYSTEM_HPP

#include "../Engine/Components/CInput.hpp"
#include "../Engine/Components/CPosition.hpp"
#include "../Engine/Components/CVelocity.hpp"

#include <entt/entity/fwd.hpp>

void sSampleSystem(entt::registry& reg);

#endif // !SSAMPLESYSTEM_HPP