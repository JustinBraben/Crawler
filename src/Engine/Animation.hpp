#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include <string>

class Animation {
	sf::Sprite m_sprite;
	std::vector<sf::IntRect> m_animFrames;
	size_t m_currentFrame = 0;	// the current frame of animation being played
	size_t m_speed = 0;			// the speed to play this animation
	sf::Vector2f m_size = { 1.f, 1.f };		// the size of the animation frame
	std::string m_name = "none";
public:

	Animation();
	Animation(const std::string& name, const sf::Texture& t, const std::vector<sf::IntRect>& animFrames, size_t speed);
};

#endif // !ANIMATION_HPP