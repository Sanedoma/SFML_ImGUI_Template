#pragma once
#include "Core/Scene.h"

class PauseScene : public Scene
{
public:
	explicit PauseScene(Game& game) : Scene(game) {}

	void handleEvent(const sf::Event& event) override;
	void Render(sf::RenderWindow& window) override;
	bool isOpaque() const override { return false; }
};
