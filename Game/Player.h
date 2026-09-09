#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Player
{
protected:
    sf::Texture texture;
    std::optional<sf::Sprite> sprite;   // sprite si une image est chargée
    sf::RectangleShape fallback;        // rectangle vert sinon
    bool hasSprite = false;

    sf::Vector2f position = { 375.f, 500.f };
    float speed = 300.f;                

public:
    Player()
    {
        // Rectangle de secours (toujours prêt)
        fallback.setSize({ 50.f, 50.f });
        fallback.setFillColor(sf::Color::Green);
        fallback.setPosition(position);

        // On tente de charger l'image ; si absente, on garde le rectangle
        if (texture.loadFromFile("assets/player.png"))
        {
            sprite.emplace(texture);
            sprite->setPosition(position);
            hasSprite = true;
        }
    }

    void Update(float deltaTime)
    {
        sf::Vector2f movement({ 0.f, 0.f });

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  movement.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) movement.x += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    movement.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  movement.y += 1.f;

        position += movement * speed * deltaTime;

		// On empêche le joueur de sortir de l'écran
        const float sizeX = 50.f;
		const float sizeY = 50.f;

        if (position.x < 0.f)            position.x = 0.f;
        if (position.y < 0.f)            position.y = 0.f;
        if (position.x > 800.f - sizeX)  position.x = 800.f - sizeX;
        if (position.y > 600.f - sizeY)  position.y = 600.f - sizeY;

        // On répercute la position sur l'objet qu'on affiche
        if (hasSprite) sprite->setPosition(position);
        else           fallback.setPosition(position);
    }

    void Render(sf::RenderWindow& window)
    {
        if (hasSprite) window.draw(sprite.value());
        else           window.draw(fallback);
    }

    sf::Vector2f getPosition() const { return position; }
};