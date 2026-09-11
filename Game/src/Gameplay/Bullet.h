#pragma once
#include <SFML/Graphics.hpp>

#include "Core/Entity.h"

class Bullet : public Entity
{
public:
	explicit Bullet(sf::Vector2f startPosition);

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;
	void OnCollision(Entity* other) override;
	sf::FloatRect getBounds() const override;
	EntityType getType() const override;

	bool isOffScreen() const;
	sf::Vector2f getPosition() const { return position; }
	void kill() { alive = false; }

protected:
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 500.f;
};
