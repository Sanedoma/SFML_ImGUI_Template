#pragma once
#include <memory>
#include <vector>
#include <random>

#include "Core/Config.h"
#include "Core/Scene.h"
#include "World/Background.h"
#include "World/Hud.h"

class Entity;
class Player;

class PlayScene : public Scene
{
public:
	explicit PlayScene(Game& game);

	void handleEvent(const sf::Event& event) override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;

private:
	void resolveExplosions();
	void spawnEnemyBullets();
	void spawnObstacles(float deltaTime);
	void handleEnemyDeaths();
	void checkCollisions();

	Background background;
	Hud hud;
	std::vector<std::unique_ptr<Entity>> entities;
	Player* player = nullptr;
	int score = 0;

	std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> buffTypeDist{ 0, 3 };
	std::uniform_int_distribution<int> dropChanceDist{ 0, 4 };

	float obstacleSpawnTimer = 1.f;
	std::uniform_real_distribution<float> obstacleIntervalDist{ 1.5f, 3.f };
	std::uniform_int_distribution<int> obstacleSizeDist{ 0, 2 };
	std::uniform_real_distribution<float> obstacleXDist{ 20.f, static_cast<float>(cfg::WindowWidth) - 20.f };
};
