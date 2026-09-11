#include "Core/SceneManager.h"

#include "Core/Scene.h"

SceneManager::SceneManager() = default;
SceneManager::~SceneManager() = default;

void SceneManager::push(std::unique_ptr<Scene> scene)
{
	commands.push_back({ Action::Push, std::move(scene) });
}

void SceneManager::pop()
{
	commands.push_back({ Action::Pop, nullptr });
}

void SceneManager::replace(std::unique_ptr<Scene> scene)
{
	commands.push_back({ Action::Replace, std::move(scene) });
}

void SceneManager::clear()
{
	commands.push_back({ Action::Clear, nullptr });
}

void SceneManager::handleEvent(const sf::Event& event)
{
	if (!scenes.empty())
		scenes.back()->handleEvent(event);
}

void SceneManager::Update(float deltaTime)
{
	if (!scenes.empty())
		scenes.back()->Update(deltaTime);
}

void SceneManager::Render(sf::RenderWindow& window)
{
	if (scenes.empty())
		return;

	std::size_t first = scenes.size() - 1;
	while (first > 0 && !scenes[first]->isOpaque())
		--first;

	for (std::size_t i = first; i < scenes.size(); ++i)
		scenes[i]->Render(window);
}

void SceneManager::applyPending()
{
	for (auto& command : commands)
	{
		switch (command.action)
		{
		case Action::Push:
			scenes.push_back(std::move(command.scene));
			break;
		case Action::Pop:
			if (!scenes.empty())
				scenes.pop_back();
			break;
		case Action::Replace:
			if (!scenes.empty())
				scenes.pop_back();
			scenes.push_back(std::move(command.scene));
			break;
		case Action::Clear:
			scenes.clear();
			break;
		}
	}
	commands.clear();
}
