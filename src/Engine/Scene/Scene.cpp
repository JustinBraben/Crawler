#include "Scene.hpp"

Scene::Scene()
{
}

Scene::Scene(GameEngine* gameEngine)
	: m_game(gameEngine)
{
	// Constructor implementation
	// You may initialize any member variables or perform other necessary actions here
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
	m_actionMap[inputKey] = actionName;
}

void Scene::registerKeyboardAction(int inputKey, const std::string& actionName)
{
	m_keyboardActionMap[inputKey] = actionName;
}

void Scene::registerMouseAction(int inputMouse, const std::string& actionName)
{
	m_MouseActionMap[inputMouse] = actionName;
}

const ActionMap& Scene::getActionMap() const
{
	return m_actionMap;
}

const ActionMap& Scene::getKeyboardActionMap() const
{
	return m_keyboardActionMap;
}

const ActionMap& Scene::getMouseActionMap() const
{
	return m_MouseActionMap;
}
