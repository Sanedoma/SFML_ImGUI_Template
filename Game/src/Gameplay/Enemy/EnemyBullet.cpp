#include "Gameplay/Enemy/EnemyBullet.h"

#include "Core/Config.h"

EnemyBullet::EnemyBullet(sf::Vector2f position)
{
	shape.setSize({ 8.f, 18.f });
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(position);
}

void EnemyBullet::Update(float deltaTime)
{
	shape.move({ 0.f, speed * deltaTime });

	if (shape.getPosition().y > static_cast<float>(cfg::WindowHeight))
		alive = false;
}

void EnemyBullet::Render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void EnemyBullet::OnCollision(Entity* other)
{
	if (other->getType() == EntityType::PLAYER)
		alive = false;
}

sf::FloatRect EnemyBullet::getBounds() const
{
	return shape.getGlobalBounds();
}

EntityType EnemyBullet::getType() const
{
	return EntityType::ENEMY_BULLET;
}
