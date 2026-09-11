#pragma once
#include "Core/Scene.h"

class MenuScene : public Scene
{
public:
	explicit MenuScene(Game& game) : Scene(game) {}

	void Render(sf::RenderWindow& window) override;
};
