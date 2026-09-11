#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Game;

class Scene
{
public:
	explicit Scene(Game& game) : game(game) {}
	virtual ~Scene() = default;

	virtual void handleEvent(const sf::Event& event) {}
	virtual void Update(float deltaTime) {}
	virtual void Render(sf::RenderWindow& window) {}

	// When false, the scene below stays visible and is drawn first.
	virtual bool isOpaque() const { return true; }

protected:
	Game& game;
};
