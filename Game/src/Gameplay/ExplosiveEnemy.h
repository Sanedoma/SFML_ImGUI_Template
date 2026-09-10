#pragma once
#include "Gameplay/Enemy.h"

// Fonce vers le joueur, s'arrete a portee puis explose apres un court delai.
class ExplosiveEnemy : public Enemy
{
public:
	explicit ExplosiveEnemy(sf::Vector2f position);

	void Update(float deltaTime) override;
	void ReactToPlayer(sf::Vector2f playerPosition, float deltaTime) override;

	bool hasExploded() const { return exploded; }
	float getExplosionRadius() const { return explosionRadius; }

private:
	float triggerDistance = 100.f;
	float explosionRadius = 150.f;
	float explosionDelay = 0.6f;
	float explosionTimer = 0.f;
	bool preparingExplosion = false;
	bool exploded = false;
};
