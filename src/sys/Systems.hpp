#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "sAllSystems.hpp"

#include <entt/entity/fwd.hpp>

class GameEngine;	// forward declaration

// Contains all the systems in place for the game
class Systems
{
protected:
	GameEngine* m_game = nullptr;
	sf::Text m_gridText;
public:
	Systems();
	Systems(GameEngine* gameEngine);
	Systems(GameEngine* gameEngine, sf::Text& gridText);
	void update(entt::registry& reg, bool drawGrid, sf::Text& gridText);
};

#endif // !SYSTEMS_HPP