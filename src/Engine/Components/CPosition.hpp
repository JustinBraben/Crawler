#ifndef CPOSITION_HPP
#define CPOSITION_HPP

#include <SFML/Graphics.hpp>
struct CPosition
{
	sf::Vector2f pos = { 0.0, 0.0 };
	sf::Vector2f prevPos = { 0.0, 0.0 };
};

#endif