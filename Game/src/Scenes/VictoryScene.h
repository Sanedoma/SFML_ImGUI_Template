#pragma once
#include "Core/Scene.h"

class VictoryScene : public Scene
{
public:
	VictoryScene(Game& game, int finalScore) : Scene(game), finalScore(finalScore) {}

	void Render(sf::RenderWindow& window) override;

private:
	int finalScore = 0;
};
