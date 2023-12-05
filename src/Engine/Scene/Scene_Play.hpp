#ifndef SCENE_PLAY_HPP
#define SCENE_PLAY_HPP

#include "Scene.hpp"

#include "../../core/Factories.hpp"

#include "../Components/CBoundingBox.hpp"
#include "../Components/CPosition.hpp"
#include "../Components/CScale.hpp"
#include "../Components/CSprite.hpp"
#include "../Components/CTile.hpp"
#include "../Components/CVelocity.hpp"

class Scene_Play : public Scene {
protected:
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;

	void init();

	void createLevel();

	void playerRender();
	void tileRender();
public:

	Scene_Play(GameEngine* gameEngine);

	void update() override;
	void onEnd() override;
	void sDoAction(const Action& action) override;
	void sRender() override;
};

#endif // !SCENE_PLAY_HPP
