#pragma once
#include <SFML/Graphics.hpp>

#include "Core/Entity.h"

// Projectile tire par un ennemi. Descend, blesse le joueur au contact.
class EnemyBullet : public Entity
{
public:
	explicit EnemyBullet(sf::Vector2f position);

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;
	void OnCollision(Entity* other) override;
	sf::FloatRect getBounds() const override;
	EntityType getType() const override;

private:
	sf::RectangleShape shape;
	float speed = 350.f;
};
