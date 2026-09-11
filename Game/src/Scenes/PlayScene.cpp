#include "Scenes/PlayScene.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <SFML/Window/Keyboard.hpp>

#include "ImGui/imgui.h"

#include "Core/Config.h"
#include "Core/Entity.h"
#include "Core/Game.h"
#include "Gameplay/Player.h"
#include "Gameplay/Enemy/Enemy.h"
#include "Gameplay/Enemy/ExplosiveEnemy.h"
#include "Gameplay/Bullet.h"
#include "Gameplay/Enemy/EnemyBullet.h"
#include "Gameplay/Buff.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/PauseScene.h"
#include "Scenes/VictoryScene.h"

PlayScene::PlayScene(Game& game, std::string levelPath)
	: Scene(game), level(std::string(cfg::AssetsRoot) + levelPath)
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
	background.Update(deltaTime);

	for (auto& entity : entities)
		entity->Update(deltaTime);

	if (player)
	{
		const sf::Vector2f playerPos = player->getPosition();
		for (auto& entity : entities)
			if (entity->getType() == EntityType::ENEMY)
				static_cast<Enemy*>(entity.get())->ReactToPlayer(playerPos, deltaTime);
	}

	resolveExplosions();

	if(player)
		if(auto bullet = player->TryShoot())
			entities.push_back(std::move(bullet));

	spawnEnemyBullets();
	spawnFromLevel(deltaTime);

	checkCollisions();

	handleEnemyDeaths();

	if (player)
		hud.Update(*player, score);

	std::erase_if(entities, [this](const std::unique_ptr<Entity>& entity)
		{
			if (entity->isAlive())
				return false;
			if (entity.get() == player)
				player = nullptr;
			return true;
		});

	if (!player)
		game.scenes().replace(std::make_unique<GameOverScene>(game, score));
	else if (level.isFinished() && !enemiesRemaining())
		game.scenes().replace(std::make_unique<VictoryScene>(game, score));
}

void PlayScene::Render(sf::RenderWindow& window)
{
	background.Render(window);

	for (auto& entity : entities)
		entity->Render(window);

	hud.Render(window);

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

void PlayScene::resolveExplosions()
{
	if (!player)
		return;

	const sf::Vector2f playerPos = player->getPosition();

	for (auto& entity : entities)
	{
		auto* bomber = dynamic_cast<ExplosiveEnemy*>(entity.get());
		if (!bomber || !bomber->hasExploded())
			continue;

		const sf::Vector2f delta = playerPos - bomber->getPosition();
		if (std::sqrt(delta.x * delta.x + delta.y * delta.y) <= bomber->getExplosionRadius())
			player->TakeDammage(2);
	}
}

void PlayScene::handleEnemyDeaths()
{
	std::vector<std::unique_ptr<Entity>> drops;

	for (auto& entity : entities)
	{
		if (entity->getType() != EntityType::ENEMY || entity->isAlive())
			continue;

		Enemy* enemy = static_cast<Enemy*>(entity.get());
		if (enemy->wasKilledByBullet())
			score += 100;

		if (dropChanceDist(rng) == 0)
		{
			BuffType type = static_cast<BuffType>(buffTypeDist(rng));
			drops.push_back(std::make_unique<Buff>(enemy->getPosition(), type));
		}
	}

	for (auto& drop : drops)
		entities.push_back(std::move(drop));
}

void PlayScene::spawnEnemyBullets()
{
	std::vector<std::unique_ptr<Entity>> fired;

	for (auto& entity : entities)
	{
		if (entity->getType() != EntityType::ENEMY)
			continue;

		Enemy* enemy = static_cast<Enemy*>(entity.get());
		if (enemy->consumeShootRequest())
		{
			const sf::Vector2f from = enemy->getPosition();
			fired.push_back(std::make_unique<EnemyBullet>(sf::Vector2f{ from.x + 16.f, from.y + 40.f }));
		}
	}

	for (auto& bullet : fired)
		entities.push_back(std::move(bullet));
}

void PlayScene::spawnFromLevel(float deltaTime)
{
	auto spawned = level.Update(deltaTime);
	for (auto& entity : spawned)
		entities.push_back(std::move(entity));
}

bool PlayScene::enemiesRemaining() const
{
	return std::any_of(entities.begin(), entities.end(),
		[](const std::unique_ptr<Entity>& entity) { return entity->getType() == EntityType::ENEMY; });
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