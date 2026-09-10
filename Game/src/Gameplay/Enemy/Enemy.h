#pragma once
#include <SFML/Graphics.hpp>

#include "Core/Entity.h"

// Base commune aux ennemis. Update() reste a la charge des sous-classes,
// qui definissent le comportement (deplacement, tir, explosion).
class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f position, float speed, int health);

	void Render(sf::RenderWindow& window) override;
	void OnCollision(Entity* other) override;
	sf::FloatRect getBounds() const override;
	EntityType getType() const override;

	// Appele chaque frame par PlayScene. Vide par defaut.
	virtual void ReactToPlayer(sf::Vector2f playerPosition, float deltaTime);
	// L'ennemi veut tirer cette frame (ShooterEnemy uniquement).
	virtual bool consumeShootRequest();

	void takeDamage(int damage);
	void kill();

	sf::Vector2f getPosition() const;
	bool wasKilledByBullet() const { return killedByBullet; }

protected:
	bool isOffScreen() const;

	sf::RectangleShape shape;
	float speed;
	int health;
	bool killedByBullet = false;
};
