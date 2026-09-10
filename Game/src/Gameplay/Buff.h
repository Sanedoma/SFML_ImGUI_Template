#pragma once
#include <SFML/Graphics.hpp>
#include "Core/Entity.h"
#include "Core/Config.h"

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

		if (isOffScreen()) {
			alive = false; // hors écran → disparaît
		}

	}

	void Render(sf::RenderWindow& window) override {
		window.draw(shape);
	}

	void OnCollision(Entity* other) override
	{
		if(other->getType() == EntityType::PLAYER) {
			alive = false;   // ramassé → disparaît
		}
	}

	BuffType getBuffType() const { return type; }
	
	EntityType getType() const override
	{
		return EntityType::BUFF;
	}

	sf::FloatRect getBounds() const override { return shape.getGlobalBounds(); }



	bool isOffScreen() const { 
		sf::FloatRect bounds = shape.getGlobalBounds();
		return bounds.position.y + bounds.size.y > static_cast<float>(cfg::WindowHeight);
	}

	sf::Vector2f getPosition() const { return position; }
};

