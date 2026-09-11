#pragma once
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "Core/Scene.h"
#include "World/Background.h"
#include "World/Hud.h"
#include "World/LevelLoader.h"

class Entity;
class Player;

class PlayScene : public Scene
{
public:
	explicit PlayScene(Game& game, std::string levelPath = "levels/level1.txt");

	void handleEvent(const sf::Event& event) override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;

private:
	void resolveExplosions();
	void spawnEnemyBullets();
	void spawnFromLevel(float deltaTime);
	void handleEnemyDeaths();
	void checkCollisions();
	bool enemiesRemaining() const;

	Background background;
	Hud hud;
	LevelLoader level;
	std::vector<std::unique_ptr<Entity>> entities;
	Player* player = nullptr;
	int score = 0;

	std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> buffTypeDist{ 0, 3 };
	std::uniform_int_distribution<int> dropChanceDist{ 0, 4 };
};
