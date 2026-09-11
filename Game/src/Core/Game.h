#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Core/SceneManager.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

	sf::RenderWindow& window() { return renderWindow; }
	SceneManager& scenes() { return sceneManager; }

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	void processEvents();

	sf::RenderWindow renderWindow;
	SceneManager sceneManager;
	sf::Clock clock;
	bool imguiReady = false;
};
