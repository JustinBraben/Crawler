#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <entt/entity/registry.hpp>

// Contains all the systems in place for the game
class Systems
{
protected:
	entt::registry m_reg;
public:
	Systems();
	void update(entt::registry& reg);
};

#endif // !SYSTEMS_HPP