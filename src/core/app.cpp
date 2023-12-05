#include "app.hpp"

Application::Application()
{
	GameEngine m_game();
}

void Application::run()
{
	std::cout << "Application is running\n";
	m_game.run();
}
