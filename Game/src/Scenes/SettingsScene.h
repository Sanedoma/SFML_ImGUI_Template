#pragma once
#include "Core/Scene.h"

class SettingsScene : public Scene
{
public:
	explicit SettingsScene(Game& game) : Scene(game) {}

	void handleEvent(const sf::Event& event) override;
	void Render(sf::RenderWindow& window) override;
	bool isOpaque() const override { return false; }

private:
	float masterVolume = 100.f;
	float musicVolume = 70.f;
};
