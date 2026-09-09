#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	sf::Texture texture;
	std::optional<sf::Sprite> sprite;
	sf::Vector2f position = { 375.f, 500.f };
	float speed = 50.f;

	Player() {
		bool result = texture.loadFromFile("assets/player.png");
		if (!result) {
			return;
		}else {
			sprite.emplace(sf::Sprite(texture));
			sprite->setPosition(position);
		}

	}

	void Update(float deltaTime) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			position.y -= speed * deltaTime;

		sprite->setPosition(position);
	}
	
	void Render(sf::RenderWindow& window) {
		window.draw(sprite.value());
	}
};

