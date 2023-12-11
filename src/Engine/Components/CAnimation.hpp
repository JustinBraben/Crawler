#ifndef CANIMATION_HPP
#define CANIMATION_HPP

#include <SFML/Graphics.hpp>

struct CAnimation {
    std::vector<sf::IntRect> animFrames;
    float frameDuration; // Duration for each frame will be the same
    float elapsedTime; // Time elapsed since the last frame change
    size_t currentFrame;
    std::string animationName;
};

#endif // !CANIMATION