#ifndef CANIMATION_HPP
#define CANIMATION_HPP

#include <SFML/Graphics.hpp>

struct CAnimation {
    std::vector<sf::IntRect> animFrames;
    float frameDuration; // Duration for each frame will be the same
    size_t currentFrame;
    float elapsedTime; // Time elapsed since the last frame change
    std::string animationName;
};

#endif // !CANIMATION