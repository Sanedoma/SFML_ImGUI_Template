#pragma once
#include "Core/Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene(Game& game, int finalScore) : Scene(game), finalScore(finalScore) {}

	void Render(sf::RenderWindow& window) override;

private:
	int finalScore = 0;
};
