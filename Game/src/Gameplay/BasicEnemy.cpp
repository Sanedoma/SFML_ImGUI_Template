#include "Gameplay/BasicEnemy.h"

BasicEnemy::BasicEnemy(sf::Vector2f position)
	: Enemy(position, 150.f, 20)
{
	shape.setFillColor(sf::Color::Red);
}

void BasicEnemy::Update(float deltaTime)
{
	shape.move({ 0.f, speed * deltaTime });

	if (isOffScreen())
		alive = false;
}
