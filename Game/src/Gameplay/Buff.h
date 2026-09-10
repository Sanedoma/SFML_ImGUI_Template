#pragma once
#include <SFML/Graphics.hpp>

#include "Core/Entity.h"

enum class BuffType
{
	Speed,
	Dammage,
	Shield,
	ExtraLife,
};

class Buff : public Entity
{
public:
	Buff(sf::Vector2f startPosition, BuffType buffType);

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;
	void OnCollision(Entity* other) override;
	sf::FloatRect getBounds() const override;
	EntityType getType() const override;

	bool isOffScreen() const;
	BuffType getBuffType() const { return type; }
	sf::Vector2f getPosition() const { return position; }

protected:
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 100.f;
	BuffType type;
};
