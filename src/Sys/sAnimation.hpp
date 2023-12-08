#ifndef SANIMATION_HPP
#define SANIMATION_HPP

#include "../Engine/Components/CInput.hpp"
#include "../Engine/Components/CPosition.hpp"
#include "../Engine/Components/CVelocity.hpp"
#include "../Engine/Components/CScale.hpp"

#include <entt/entity/fwd.hpp>

void sAnimation(entt::registry& reg);

#endif // !SANIMATION_HPP