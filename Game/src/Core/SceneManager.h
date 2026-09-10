#pragma once
#include <memory>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Scene;

// Stack of scenes. Events and updates go to the top scene only; rendering
// starts at the lowest visible scene so non-opaque scenes act as overlays
// (pause, settings). Transitions are queued and applied once per frame.
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void push(std::unique_ptr<Scene> scene);
	void pop();
	void replace(std::unique_ptr<Scene> scene);
	void clear();

	void handleEvent(const sf::Event& event);
	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

	void applyPending();
	bool empty() const { return scenes.empty(); }

private:
	enum class Action { Push, Pop, Replace, Clear };

	struct Command
	{
		Action action;
		std::unique_ptr<Scene> scene;
	};

	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<Command> commands;
};
