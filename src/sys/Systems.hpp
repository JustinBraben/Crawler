#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <entt/entity/fwd.hpp>

// Contains all the systems in place for the game
class Systems
{
public:
	Systems();
	void update(entt::registry& reg);
};

#endif // !SYSTEMS_HPP