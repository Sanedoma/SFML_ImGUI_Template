#include "Gameplay/ExplosiveEnemy.h"

#include <cmath>

ExplosiveEnemy::ExplosiveEnemy(sf::Vector2f position)
	: Enemy(position, 120.f, 10)
{
	shape.setFillColor(sf::Color::Blue);
}

void ExplosiveEnemy::Update(float deltaTime)
{
	if (!preparingExplosion)
		return;

	explosionTimer += deltaTime;
	if (explosionTimer >= explosionDelay)
	{
		exploded = true;
		alive = false;
	}
}

void ExplosiveEnemy::ReactToPlayer(sf::Vector2f playerPosition, float deltaTime)
{
	if (preparingExplosion)
		return;

	const sf::Vector2f center = shape.getPosition() + sf::Vector2f{ 20.f, 20.f };
	const sf::Vector2f target = playerPosition + sf::Vector2f{ 25.f, 25.f };
	const sf::Vector2f delta = target - center;
	const float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

	if (distance <= triggerDistance)
	{
		preparingExplosion = true;
		explosionTimer = 0.f;
		shape.setFillColor(sf::Color::Magenta);
		return;
	}

	if (distance > 0.f)
		shape.move((delta / distance) * speed * deltaTime);
}
