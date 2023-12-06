#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <entt/entity/fwd.hpp>
#include <SFML/Graphics.hpp>

#include "../Engine/Components/CBoundingBox.hpp"
#include "../Engine/Components/CEnemy.hpp"
#include "../Engine/Components/CName.hpp"
#include "../Engine/Components/CPlayer.hpp"
#include "../Engine/Components/CPosition.hpp"
#include "../Engine/Components/CScale.hpp"
#include "../Engine/Components/CSprite.hpp"
#include "../Engine/Components/CTile.hpp"
#include "../Engine/Components/CVelocity.hpp"

#include "../configs/Constants.hpp"

#include <entt/entity/registry.hpp>

entt::entity makePlayer(entt::registry& reg, sf::Sprite& sprite, sf::IntRect& textureRect, sf::Vector2f& pos);
entt::entity makeTile(entt::registry& reg, sf::Sprite& sprite, sf::IntRect& textureRect, sf::Vector2f& pos);
entt::entity makeFloor(entt::registry& reg, sf::Sprite& sprite, sf::IntRect& textureRect, sf::Vector2f& pos);

void makeRoom(entt::registry& reg, sf::Sprite& sprite, sf::Vector2f& startingPos);

#endif // !FACTORIES_HPP
