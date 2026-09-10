#include "Gameplay/Enemy/Enemy.h"

#include "Core/Config.h"

Enemy::Enemy(sf::Vector2f position, float speed, int health)
	: speed(speed), health(health)
{
	shape.setSize({ 40.f, 40.f });
	shape.setPosition(position);
}

void Enemy::Render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Enemy::OnCollision(Entity* other)
{
	if (other->getType() == EntityType::BULLET)
	{
		takeDamage(10);
		if (!alive)
			killedByBullet = true;
	}
	else if (other->getType() == EntityType::PLAYER)
	{
		killedByBullet = false;
		kill();
	}
}

sf::FloatRect Enemy::getBounds() const
{
	return shape.getGlobalBounds();
}

EntityType Enemy::getType() const
{
	return EntityType::ENEMY;
}

void Enemy::ReactToPlayer(sf::Vector2f, float)
{
}

bool Enemy::consumeShootRequest()
{
	return false;
}

void Enemy::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		health = 0;
		alive = false;
	}
}

void Enemy::kill()
{
	health = 0;
	alive = false;
}

sf::Vector2f Enemy::getPosition() const
{
	return shape.getPosition();
}

bool Enemy::isOffScreen() const
{
	return shape.getPosition().y > static_cast<float>(cfg::WindowHeight);
}
