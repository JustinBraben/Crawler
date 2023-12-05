#include "Scene_Play.hpp"
#include "../GameEngine.hpp"

Scene_Play::Scene_Play(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Play::init()
{
	registerAction(sf::Keyboard::Escape, "QUIT");

	createLevel();
}

void Scene_Play::createLevel()
{
	// TODO: create some basic entities to render to the screen for now
	m_reg.clear();

	sf::Sprite playerSprite;
	auto& playerTexture = m_game->getAssets().getTexture("players blue x1");
	playerSprite.setTexture(playerTexture);
	sf::IntRect playerRect = { 0, 0, 32, 32 };
	//playerSprite.setTextureRect(playerRect);

	const auto playerEntity = makePlayer(m_reg, playerSprite, playerRect);

	sf::Sprite tileSprite;
	auto& tileTexture = m_game->getAssets().getTexture("tileset x1");
	tileSprite.setTexture(tileTexture);
	sf::IntRect tileRect = { 34 * 32, 1 * 32, 32, 32 };
	sf::Vector2f tilePos = { 300.f, 300.f };

	const auto tileEntity = makeTile(m_reg, tileSprite, tileRect, tilePos);
	std::cout << "Created Level with new Player \n";
}

void Scene_Play::playerRender()
{
	const auto playerView = m_reg.view<CPlayer, CBoundingBox, CPosition, CVelocity, CScale, CSprite>();

	for (const auto& player : playerView)
	{
		auto& pos = playerView.get<CPosition>(player).pos;
		auto& box = playerView.get<CBoundingBox>(player);
		auto& velocity = playerView.get<CVelocity>(player).vel;
		auto& scale = playerView.get<CScale>(player).scale;
		auto& sprite = playerView.get<CSprite>(player).id;
		auto& texRect = playerView.get<CSprite>(player).texRect;
		sprite.setTextureRect(texRect);
		sprite.setOrigin(box.halfSize);
		sprite.setPosition(pos);
		sprite.setScale(scale);
		m_game->window().draw(sprite);
	}
}

void Scene_Play::tileRender()
{
	const auto tileView = m_reg.view<CTile, CBoundingBox, CPosition, CScale, CSprite>();

	for (const auto& tile : tileView)
	{
		auto& pos = tileView.get<CPosition>(tile).pos;
		auto& box = tileView.get<CBoundingBox>(tile);
		auto& scale = tileView.get<CScale>(tile).scale;
		auto& sprite = tileView.get<CSprite>(tile).id;
		auto& texRect = tileView.get<CSprite>(tile).texRect;
		sprite.setTextureRect(texRect);
		sprite.setOrigin(box.halfSize);
		sprite.setPosition(pos);
		sprite.setScale(scale);
		m_game->window().draw(sprite);
	}
}

void Scene_Play::update()
{
	sRender();
}

void Scene_Play::onEnd()
{
	// These actions are here to stop the player from continuously moving
	// when holding a movement key down and exiting the play scene
	sDoAction(Action("MOVE_LEFT", "END"));
	sDoAction(Action("MOVE_RIGHT", "END"));
	sDoAction(Action("MOVE_DOWN", "END"));
	sDoAction(Action("MOVE_UP", "END"));

	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.type() == "START") 
	{

	}
	
	if (action.type() == "END")
	{
		if (action.name() == "QUIT")
		{
			onEnd();
		}
	}
}

void Scene_Play::sRender()
{
	// color the background darker so you know that the game is paused
	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	playerRender();

	tileRender();

	m_game->window().display();
}
