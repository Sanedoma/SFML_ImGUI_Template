#pragma once
#include <SFML/Graphics.hpp>
#include "../Core/Entity.h"

enum class BuffType {
	Speed,
	Dammage,
	Shield,
	ExtraLife,
};

class Buff : public Entity
{
protected:
	sf::RectangleShape shape;
	sf::Vector2f position;
	float speed = 100.f;
	BuffType type;

public:
	Buff(sf::Vector2f startPosition, BuffType buffType){
		position = startPosition;
		type = buffType;

		shape.setSize({ 24.f, 24.f });
		shape.setPosition(position);

		switch (type) {
		case BuffType::Speed:
			shape.setFillColor(sf::Color::Cyan);
			break;
		case BuffType::Dammage:
			shape.setFillColor(sf::Color::Magenta);
			break;
		case BuffType::Shield:
			shape.setFillColor(sf::Color::Blue);
			break;
		case BuffType::ExtraLife:
			shape.setFillColor(sf::Color::Green);
			break;
		}
	}

	void Update(float deltaTime) override {
		position.y += speed * deltaTime;
		shape.setPosition(position);

	}

	void Render(sf::RenderWindow& window) override {
		window.draw(shape);
	}

	void OnCollision(Entity* other) override
	{
		alive = false;   // ramassé → disparaît
	}

	BuffType getType() const { return type; }

	sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

	bool isOffScreen() const { return position.y > 600.f; }

	sf::Vector2f getPosition() const { return position; }
};

