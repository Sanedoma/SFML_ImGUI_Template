#pragma once
#include <SFML/Graphics.hpp>

#include "Core/Entity.h"

class Player : public Entity
{
protected:
	sf::Texture texture;
	sf::Vector2f position = { 375.f, 500.f };
	float speed = 50.f;

public:
	Player() {
		if (!texture.loadFromFile("assets/player.png"))
			return;

		sprite.emplace(texture);
		sprite->setPosition(position);
	}

	void Update(float deltaTime) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			position.y -= speed * deltaTime;

		if (sprite.has_value())
			sprite->setPosition(position);
	}

	void OnCollision(Entity* other) override
	{
		// TODO
	}

	sf::Vector2f getPosition() const { return position; }
};
