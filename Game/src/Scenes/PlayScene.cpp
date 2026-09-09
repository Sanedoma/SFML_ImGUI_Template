#include "Scenes/PlayScene.h"

#include <SFML/Window/Keyboard.hpp>

#include "ImGui/imgui.h"

#include "Core/Entity.h"
#include "Core/Game.h"
#include "Gameplay/Player.h"
#include "Scenes/PauseScene.h"

PlayScene::PlayScene(Game& game)
	: Scene(game)
{
	auto newPlayer = std::make_unique<Player>();
	player = newPlayer.get();
	entities.push_back(std::move(newPlayer));
}

void PlayScene::handleEvent(const sf::Event& event)
{
	const auto* key = event.getIf<sf::Event::KeyPressed>();
	if (key && key->code == sf::Keyboard::Key::Escape)
		game.scenes().push(std::make_unique<PauseScene>(game));
}

void PlayScene::Update(float deltaTime)
{
	for (auto& entity : entities)
		entity->Update(deltaTime);

	checkCollisions();

	std::erase_if(entities, [this](const std::unique_ptr<Entity>& entity)
	{
		if (entity->isAlive())
			return false;
		if (entity.get() == player)
			player = nullptr;
		return true;
	});
}

void PlayScene::Render(sf::RenderWindow& window)
{
	for (auto& entity : entities)
		entity->Render(window);

	ImGui::Begin("Debug");
	if (player)
		ImGui::Text("Player: (%.0f, %.0f)", player->getPosition().x, player->getPosition().y);
	ImGui::Text("Score: %d", score);
	ImGui::End();
}

void PlayScene::checkCollisions()
{
	for (std::size_t i = 0; i < entities.size(); ++i)
		for (std::size_t j = i + 1; j < entities.size(); ++j)
		{
			if (entities[i]->getBounds().findIntersection(entities[j]->getBounds()))
			{
				entities[i]->OnCollision(entities[j].get());
				entities[j]->OnCollision(entities[i].get());
			}
		}
}
