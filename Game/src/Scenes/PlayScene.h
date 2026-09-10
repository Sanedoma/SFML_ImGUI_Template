#pragma once
#include <memory>
#include <vector>
#include <random>

#include "Core/Scene.h"

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
	void checkCollisions();

	std::vector<std::unique_ptr<Entity>> entities;
	Player* player = nullptr;
	int score = 0;

	std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> buffTypeDist{ 0, 3 };
	std::uniform_int_distribution<int> dropChanceDist{ 0, 4 };
};
