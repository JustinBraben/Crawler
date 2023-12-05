#include "../Engine/GameEngine.hpp"

class Application {
protected:
	GameEngine m_game;
public:
	Application();
	void run();
};