#pragma once
#include "GameState.h"
class GameOverState : public GameState {
public:
    void init() override;
    void handleInput(sf::Event event) override;
    void update(float dt) override;
    void render() override;

private:
    sf::Text m_gameOverText;
    sf::Font m_font;
};


