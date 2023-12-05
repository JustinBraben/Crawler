#include "Scene_Menu.hpp"
#include "../GameEngine.hpp"


void Scene_Menu::onEnd()
{
	m_game->quit();
}

void Scene_Menu::update()
{
	sRender();
}

void Scene_Menu::sDoAction(const Action& action)
{
	if (action.name() == "QUIT")
	{
		onEnd();
	}
}

void Scene_Menu::sRender()
{
	m_game->window().clear(sf::Color(173, 216, 230));

	// Render title
	m_game->window().draw(m_menuText);

	m_game->window().display();
}

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	// Constructor implementation
	// You may initialize any member variables or perform other necessary actions here
	m_title = "Crawler";
	init();
}

void Scene_Menu::init()
{
	// TODO: Register actions for Scene_Menu
	registerAction(sf::Keyboard::Escape, "QUIT");	// QUIT out of the game
	registerAction(sf::Keyboard::W, "UP");			// Go UP in menu
	registerAction(sf::Keyboard::S, "DOWN");		// Go DOWN in menu
	registerAction(sf::Keyboard::D, "PLAY");		// Toggle drawing (G)rid

	auto& menuFont = m_game->getAssets().getFont("Neoteric-32A8");
	m_menuText.setFont(menuFont);
	m_menuText.setString(m_title);
	m_menuText.setFillColor(sf::Color::Black);
	m_menuText.setCharacterSize(32);
	m_menuText.setPosition(10, 10);  // Adjust the position as needed
}