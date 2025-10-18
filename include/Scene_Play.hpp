#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "Core.hpp"
#include "EntityManager.hpp"
#include "GameEngine.hpp"
#include "Scene.hpp"

class Scene_Play : public Scene {
	struct PlayerConfig {
		float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
		std::string WEAPON;
	};

protected:
	std::shared_ptr<Entity> m_player;
	std::string m_levelPath;
	PlayerConfig m_playerConfig;
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;
	const Vec2f m_gridSize = { 64, 64 };

	void init(const std::string& levelPath);
	void update() override;

	void loadLevel(const std::string& filename);

	void onEnd();

	void sAnimation();
	void sCollision();
	void sDoAction(const Action& action) override;
	void sEnemySpawner();
	void sGUI();
	void sLifespan();
	void sMovement();
	void sRender() override;

public:
	Scene_Play(std::shared_ptr<GameEngine> gameEngine, const std::string& levelPath);

	Vec2f gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	void spawnPlayer();
	void spawnBullet(std::shared_ptr<Entity> entity);

	void onFrame();
};

template void GameEngine::changeScene<Scene_Play>(
	const std::string&, std::shared_ptr<Scene_Play>);
