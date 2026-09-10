#pragma once
#include <SFML/Graphics.hpp>
#include "Core/Entity.h"
#include "Core/Config.h"

class Bullet : public Entity
{
protected:
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 500.f;

public:
	Bullet(sf::Vector2f startPosition) {
		position = startPosition;
		shape.setSize({ 6.f, 16.f });
		shape.setFillColor(sf::Color::Yellow);
		shape.setPosition(position);

	}

	void Update(float deltaTime) override{
		position.y -= speed * deltaTime;
		shape.setPosition(position);

		if (isOffScreen()) {
			alive = false; // hors écran → disparaît
		}
	}

	void Render(sf::RenderWindow& window) override {
		window.draw(shape);
	}

	void OnCollision(Entity* other) override {
		if (other->getType() == EntityType::ENEMY) {
			alive = false; // disparaît à l'impact
		}
	}

	sf::FloatRect getBounds() const override
	{
		return shape.getGlobalBounds();
	}

	EntityType getType() const override
	{
		return EntityType::BULLET;
	}

	bool isOffScreen() const
	{
		sf::FloatRect bounds = shape.getGlobalBounds();
		return bounds.position.y + bounds.size.y < 0.f;
	}


	sf::Vector2f getPosition() const { return position; }
	void kill() { alive = false; }
};

