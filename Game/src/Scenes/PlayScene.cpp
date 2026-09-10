#include "Scenes/PlayScene.h"

#include <memory>
#include <SFML/Window/Keyboard.hpp>

#include "ImGui/imgui.h"

#include "Core/Entity.h"
#include "Core/Game.h"
#include "Gameplay/Player.h"
#include "Gameplay/Enemy.h"
#include "Gameplay/BasicEnemy.h"
#include "Gameplay/Bullet.h"
#include "Gameplay/Buff.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/PauseScene.h"
#include "Scenes/VictoryScene.h"

PlayScene::PlayScene(Game& game)
	: Scene(game)
{
	auto newPlayer = std::make_unique<Player>();
	player = newPlayer.get();
	entities.push_back(std::move(newPlayer));

	// Quelques ennemis de test
	entities.push_back(std::make_unique<BasicEnemy>(sf::Vector2f{ 100.f, 0.f }));
	entities.push_back(std::make_unique<BasicEnemy>(sf::Vector2f{ 300.f, -100.f }));
	entities.push_back(std::make_unique<BasicEnemy>(sf::Vector2f{ 500.f, -200.f }));
	entities.push_back(std::make_unique<BasicEnemy>(sf::Vector2f{ 700.f, -50.f }));
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

	if(player)
		if(auto bullet = player->TryShoot())
			entities.push_back(std::move(bullet));

	checkCollisions();

	for (auto& entity : entities)
	{
		if (entity->getType() == EntityType::ENEMY && !entity->isAlive())
		{
			Enemy* enemy = static_cast<Enemy*>(entity.get());
			if(enemy->wasKilledByBullet())
				score += 100;

			if (dropChanceDist(rng) == 0)
			{
				int r = buffTypeDist(rng);
				BuffType type = static_cast<BuffType>(r);
				entities.push_back(std::make_unique<Buff>(enemy->getPosition(), type));
			}
		}
	}

	std::erase_if(entities, [this](const std::unique_ptr<Entity>& entity)
		{
			if (entity->isAlive())
				return false;
			if (entity.get() == player)
				player = nullptr;
			return true;
		});
	if(!player)
		game.scenes().replace(std::make_unique<GameOverScene>(game, score));
}

void PlayScene::Render(sf::RenderWindow& window)
{
	for (auto& entity : entities)
		entity->Render(window);

	ImGui::Begin("Debug");
	if (player) {
		ImGui::Text("Player: (%.0f, %.0f)", player->getPosition().x, player->getPosition().y);
		ImGui::Text("Health: %d", player->getHealth());
	}
	ImGui::Text("Score: %d", score);
	ImGui::Text("Entities: %d", (int)entities.size());
	if (ImGui::Button("Tuer le joueur"))
		game.scenes().replace(std::make_unique<GameOverScene>(game, score));
	if (ImGui::Button("Gagner"))
		game.scenes().replace(std::make_unique<VictoryScene>(game, score));
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