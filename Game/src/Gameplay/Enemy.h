#pragma once
#include <SFML/Graphics.hpp>
#include "../Core/Entity.h"

class Enemy : public Entity
{
protected:
	sf::RectangleShape fallback;
	sf::Vector2f position;
	float speed = 100.f;

public:
	Enemy(sf::Vector2f startPosition){
		position = startPosition;
		fallback.setSize({ 40.f, 40.f });
		fallback.setFillColor(sf::Color::Red);
		fallback.setPosition(position);
	}

	void Update(float deltaTime)override {
		position.y += speed * deltaTime;
		fallback.setPosition(position);
	}

	void Render(sf::RenderWindow& window) override {
		window.draw(fallback);
	}

	void OnCollision(Entity* other) override {
		if (other->getType() == EntityType::BULLET ||
			other->getType() == EntityType::PLAYER) {
			alive = false;
		}
	}

	sf::FloatRect getBounds() const override{
		return fallback.getGlobalBounds();
	}

	EntityType getType() const override
	{
		return EntityType::ENEMY;
	}

	sf::Vector2f getPosition() const { return position; }

	bool isOffScreen() const {
		return position.y > 600.f;
	}
};

