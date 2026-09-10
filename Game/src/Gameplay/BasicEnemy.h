#pragma once
#include "Gameplay/Enemy.h"

// Descend tout droit vers le bas.
class BasicEnemy : public Enemy
{
public:
	explicit BasicEnemy(sf::Vector2f position);

	void Update(float deltaTime) override;
};
