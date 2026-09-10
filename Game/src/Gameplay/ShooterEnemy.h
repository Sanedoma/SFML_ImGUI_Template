#pragma once
#include "Gameplay/Enemy.h"

// Stationnaire, tire vers le bas a intervalle regulier.
class ShooterEnemy : public Enemy
{
public:
	explicit ShooterEnemy(sf::Vector2f position);

	void Update(float deltaTime) override;
	bool consumeShootRequest() override;

private:
	float shootTimer = 0.f;
	float shootCooldown = 1.5f;
	bool wantsToShoot = false;
};
