#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics.hpp>

#include "../Engine/Components/CBoundingBox.hpp"
#include "../Engine/Components/CEnemy.hpp"
#include "../Engine/Components/CPlayer.hpp"
#include "../Engine/Components/CPosition.hpp"
#include "../Engine/Components/CScale.hpp"
#include "../Engine/Components/CSprite.hpp"
#include "../Engine/Components/CVelocity.hpp"

#include "../configs/Constants.hpp"

#include <entt/entity/registry.hpp>

entt::entity makePlayer(entt::registry& reg, sf::Sprite& sprite, sf::IntRect& textureRect);

#endif // !FACTORIES_HPP
