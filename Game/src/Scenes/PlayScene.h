#pragma once
#include <memory>
#include <vector>

#include "Core/Scene.h"

class Entity;
class Player;

class PlayScene : public Scene
{
public:
	explicit PlayScene(Game& game);

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;

private:
	void checkCollisions();

	std::vector<std::unique_ptr<Entity>> entities;
	Player* player = nullptr;
	int score = 0;
};
