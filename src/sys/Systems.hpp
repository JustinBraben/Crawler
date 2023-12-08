#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "sMovement.hpp"
#include "sAnimation.hpp"

#include <entt/entity/fwd.hpp>

class GameEngine;	// forward declaration

// Contains all the systems in place for the game
class Systems
{
protected:
	GameEngine* m_game = nullptr;
public:
	Systems();
	Systems(GameEngine* gameEngine);
	void update(entt::registry& reg);
};

#endif // !SYSTEMS_HPP