#ifndef CBOUNDINGBOX_HPP
#define CBOUNDINGBOX_HPP

#include <SFML/Graphics.hpp>

struct CBoundingBox {
	sf::Vector2f size;
	sf::Vector2f halfSize;
};

#endif // !CBOUNDINGBOX_HPP