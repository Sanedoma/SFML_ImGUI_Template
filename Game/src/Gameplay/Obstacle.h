#pragma once
#include "Core/Entity.h"

// Palier de taille : determine le sprite, la vitesse et les degats au contact.
enum class ObstacleSize { Big, Medium, Tiny };

// Meteore a la derive. Indestructible aux tirs (ils le traversent), mais
// disparait au contact du joueur en lui infligeant ses degats.
class Obstacle : public Entity
{
public:
	Obstacle(sf::Vector2f position, ObstacleSize size);

	void Update(float deltaTime) override;
	void OnCollision(Entity* other) override;
	EntityType getType() const override;

	int getContactDamage() const { return contactDamage; }

private:
	bool isOffScreen() const;

	float speed;
	int contactDamage;
};
