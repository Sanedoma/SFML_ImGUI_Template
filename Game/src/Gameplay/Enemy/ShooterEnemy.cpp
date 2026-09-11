#include "Gameplay/Enemy/ShooterEnemy.h"

namespace
{
	constexpr float EntrySpeed = 80.f;
	constexpr float HoldY = 80.f; // position ou l'ennemi s'arrete pour tirer
}

ShooterEnemy::ShooterEnemy(sf::Vector2f position)
	: Enemy(position, EntrySpeed, 3)
{
	shape.setFillColor(sf::Color::Yellow);

	if (position.y >= HoldY)
		inPosition = true;
}

void ShooterEnemy::Update(float deltaTime)
{
	if (!inPosition)
	{
		shape.move({ 0.f, speed * deltaTime });
		if (shape.getPosition().y >= HoldY)
		{
			shape.setPosition({ shape.getPosition().x, HoldY });
			inPosition = true;
		}
		return;
	}

	shootTimer += deltaTime;

	if (shootTimer >= shootCooldown)
	{
		wantsToShoot = true;
		shootTimer = 0.f;
	}
}

bool ShooterEnemy::consumeShootRequest()
{
	if (wantsToShoot)
	{
		wantsToShoot = false;
		return true;
	}
	return false;
}
