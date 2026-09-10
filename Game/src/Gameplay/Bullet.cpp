#include "Gameplay/Bullet.h"

Bullet::Bullet(sf::Vector2f startPosition)
	: position(startPosition)
{
	shape.setSize({ 6.f, 16.f });
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(position);
}

void Bullet::Update(float deltaTime)
{
	position.y -= speed * deltaTime;
	shape.setPosition(position);

	if (isOffScreen())
		alive = false;
}

void Bullet::Render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Bullet::OnCollision(Entity* other)
{
	if (other->getType() == EntityType::ENEMY)
		alive = false;
}

sf::FloatRect Bullet::getBounds() const
{
	return shape.getGlobalBounds();
}

EntityType Bullet::getType() const
{
	return EntityType::BULLET;
}

bool Bullet::isOffScreen() const
{
	const sf::FloatRect bounds = shape.getGlobalBounds();
	return bounds.position.y + bounds.size.y < 0.f;
}
