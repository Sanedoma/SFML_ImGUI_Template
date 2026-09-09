#pragma once
#include <SFML/Graphics.hpp>

class Bullet
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

	void Update(float deltaTime) {
		position.y -= speed * deltaTime;
		shape.setPosition(position);
	}

	void Render(sf::RenderWindow& window) {
		window.draw(shape);
	}

	bool isOffScreen() const {
		return position.y + 16.f < 0;
	}

	sf::Vector2f getPosition() const { return position; }
};

