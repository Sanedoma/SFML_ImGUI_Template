#include "Gameplay/ShooterEnemy.h"

ShooterEnemy::ShooterEnemy(sf::Vector2f position)
	: Enemy(position, 0.f, 3)
{
	shape.setFillColor(sf::Color::Yellow);
}

void ShooterEnemy::Update(float deltaTime)
{
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
