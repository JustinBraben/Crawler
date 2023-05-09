#pragma once
#include "GameState.h"

class GameRunningState : public GameState
{
public:
	GameRunningState(std::shared_ptr<sf::RenderWindow> window) : GameState(window) {}


};

