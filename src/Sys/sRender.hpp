#ifndef SRENDER_HPP
#define SRENDER_HPP

#include "../Engine/Components/CBoundingBox.hpp"
#include "../Engine/Components/CInput.hpp"
#include "../Engine/Components/CName.hpp"
#include "../Engine/Components/CPlayer.hpp"
#include "../Engine/Components/CPosition.hpp"
#include "../Engine/Components/CVelocity.hpp"
#include "../Engine/Components/CTile.hpp"
#include "../Engine/Components/CSprite.hpp"
#include "../Engine/Components/CScale.hpp"

#include <entt/entity/fwd.hpp>

class GameEngine;	// forward declaration

void sRender(
	entt::registry& reg, 
	GameEngine* gameEngine, 
	bool drawGrid,
	sf::Text& gridText
);

void sFloorRender(entt::registry& reg, GameEngine* gameEngine);

void sWallRender(entt::registry& reg, GameEngine* gameEngine);

void sPlayerRender(entt::registry& reg, GameEngine* gameEngine);

void sGridRender(entt::registry& reg, GameEngine* gameEngine, sf::Text& gridText);

void sCamera(entt::registry& reg, GameEngine* gameEngine);

float smoothCameraFollow(float x, float y, float adjust);

sf::Vector2i pixelToGrid(sf::Vector2f& pos);

void drawLine(const sf::Vector2f& p1, const sf::Vector2f& p2, GameEngine* gameEngine);

#endif // !SRENDER_HPP