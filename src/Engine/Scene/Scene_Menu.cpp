#include "Scene_Menu.hpp"
#include "Scene_Play.hpp"
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
	if (action.type() == "END")
	{
		if (action.name() == "UP") {
			// Only decrease the index if it's not already at the top
			if (m_selectedMenuIndex > 0)
				m_selectedMenuIndex--;
		}
		if (action.name() == "DOWN") {
			// Only increase the index if it's not already at the bottom
			if (m_selectedMenuIndex < m_menuStrings.size() - 1)
				m_selectedMenuIndex++;
		}
		if (action.name() == "QUIT")
		{
			onEnd();
		}
		if (action.name() == "SELECT")
		{
			std::filesystem::path levelToLoad = savesPath;
			levelToLoad.append(m_menuStrings[m_selectedMenuIndex] + ".json");
			auto newScenePlay = std::make_shared<Scene_Play>(m_game, levelToLoad);
			m_game->changeScene("PLAY_" + m_menuStrings[m_selectedMenuIndex], newScenePlay);
		}
	}
}

void Scene_Menu::sRender()
{
	m_game->window().clear(sf::Color(173, 216, 230));

	// Render title
	m_game->window().draw(m_menuText);

	// Render level names
	sf::Text choiceText;
	auto& menuFont = m_game->getAssets().getFont("arial");
	choiceText.setFont(menuFont);
	choiceText.setCharacterSize(24);
	float textSpacing = 30.f;
	int numOptions = 0;
	for (const auto& textOption : m_menuStrings)
	{
		choiceText.setString(textOption);
		choiceText.setFillColor(numOptions == m_selectedMenuIndex ? sf::Color::White : sf::Color::Black);
		choiceText.setPosition(20, 100 + numOptions * textSpacing);
		m_game->window().draw(choiceText);
		numOptions += 1;
	}

	// Render navigation instructions
	sf::Text instructions;
	instructions.setFont(menuFont);
	instructions.setCharacterSize(20);
	instructions.setFillColor(sf::Color::Black);
	instructions.setString("UP : W    DOWN : S    SELECT : D    BACK : ESC");
	instructions.setPosition(0, m_game->window().getSize().y - 50); // Bottom of the window
	m_game->window().draw(instructions);

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
	registerKeyboardAction(sf::Keyboard::Escape, "QUIT");	// QUIT out of the game
	registerKeyboardAction(sf::Keyboard::W, "UP");			// Go UP in menu
	registerKeyboardAction(sf::Keyboard::S, "DOWN");		// Go DOWN in menu
	registerKeyboardAction(sf::Keyboard::D, "SELECT");		// Toggle drawing (G)rid

	// TODO: load menu strings
	std::filesystem::path assetsPath(savesPath);

	loadMenuPaths(savesPath);

	auto& menuFont = m_game->getAssets().getFont("AboveDemoRegular-lJMd");
	m_menuText.setFont(menuFont);
	m_menuText.setString(m_title);
	m_menuText.setFillColor(sf::Color::Black);
	m_menuText.setCharacterSize(64);
	m_menuText.setPosition(10, 10);  // Adjust the position as needed
}

void Scene_Menu::loadMenuPaths(const std::filesystem::path& folderPath)
{
	for (auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		auto filePath = entry.path();
		auto extension = filePath.extension().string();
		if (extension == ".json")
		{
			auto stem = filePath.stem().string();
			m_menuStrings.push_back(stem);
		}
	}
}
