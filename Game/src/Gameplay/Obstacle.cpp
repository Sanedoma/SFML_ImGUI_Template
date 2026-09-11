#include "Gameplay/Obstacle.h"

#include <array>
#include <random>

#include "Core/AssetManager.h"
#include "Core/Config.h"

namespace
{
	struct Tier
	{
		float speed;
		int damage;
		std::array<const char*, 2> sprites;
	};

	const Tier& tierFor(ObstacleSize size)
	{
		static const Tier tiers[] = {
			{ 70.f,  2, { "obstacles/meteor_big_1.png",    "obstacles/meteor_big_2.png" } },
			{ 110.f, 1, { "obstacles/meteor_medium_1.png", "obstacles/meteor_medium_2.png" } },
			{ 160.f, 0, { "obstacles/meteor_tiny_1.png",   "obstacles/meteor_tiny_2.png" } },
		};
		return tiers[static_cast<int>(size)];
	}
}

Obstacle::Obstacle(sf::Vector2f position, ObstacleSize size)
{
	const Tier& tier = tierFor(size);
	speed = tier.speed;
	contactDamage = tier.damage;

	static std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> variant(0, static_cast<int>(tier.sprites.size()) - 1);

	sprite.emplace(AssetManager::instance().texture(tier.sprites[variant(rng)]));
	sprite->setPosition(position);
}

void Obstacle::Update(float deltaTime)
{
	sprite->move({ 0.f, speed * deltaTime });

	if (isOffScreen())
		alive = false;
}

void Obstacle::OnCollision(Entity* other)
{
	if (other->getType() == EntityType::PLAYER)
		alive = false;
}

EntityType Obstacle::getType() const
{
	return EntityType::OBSTACLE;
}

bool Obstacle::isOffScreen() const
{
	const sf::FloatRect bounds = sprite->getGlobalBounds();
	return bounds.position.y > static_cast<float>(cfg::WindowHeight);
}
