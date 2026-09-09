#pragma once
#include <SFML/Graphics.hpp>
#include "../Core/Entity.h"

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
	}

	void Render(sf::RenderWindow& window) override {
		window.draw(shape);
	}

	void OnCollision(Entity* other) override {
		// Todo
	}

	sf::FloatRect getBounds() const {
		return shape.getGlobalBounds();
	}

	bool isOffScreen() const {
		return position.y + 16.f < 0;
	}

	sf::Vector2f getPosition() const { return position; }
	void kill() { alive = false; }
};

