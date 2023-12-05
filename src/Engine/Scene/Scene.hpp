#ifndef SCENE_HPP
#define SCENE_HPP

#include "../Action/Action.hpp"

#include <entt/entity/registry.hpp>

#include <memory>
#include <map>

class GameEngine;	// forward declaration

using ActionMap = std::map<int, std::string>;

class Scene
{
protected:
	GameEngine* m_game = nullptr;
	entt::registry m_reg;
	ActionMap m_actionMap;
	bool m_paused = false;
	bool m_hasEnded = false;
public:

	virtual void onEnd() = 0;
	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;

	Scene();
	Scene(GameEngine* gameEngine);

	void registerAction(int inputKey, const std::string& actionName);

	bool hasEnded() const;
	const ActionMap& getActionMap() const;
};

#endif // !SCENE_HPP