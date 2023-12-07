#ifndef CSPRITE_HPP
#define CSPRITE_HPP

#include <SFML/Graphics.hpp>

struct CSprite {
	sf::Sprite id;
	sf::IntRect texRect;
	std::string textureName;
};

#endif // !CSPRITE_HPP