#ifndef CRENDER_HPP
#define CRENDER_HPP

#include <SFML/Graphics.hpp>

struct CRender {
    sf::Sprite sprite;
    std::string name; // Debugging-friendly identifier
};

#endif // ! CRENDER_HPP