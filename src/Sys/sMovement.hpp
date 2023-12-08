#ifndef SMOVEMENT_HPP
#define SMOVEMENT_HPP

#include <algorithm>

#include "../configs/Constants.hpp"

#include "../Engine/Components/CInput.hpp"
#include "../Engine/Components/CPosition.hpp"
#include "../Engine/Components/CVelocity.hpp"

#include <entt/entity/fwd.hpp>

void sMovement(entt::registry& reg);

#endif // !SMOVEMENT_HPP