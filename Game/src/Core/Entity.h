#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Entity
{
protected:
    std::optional<sf::Sprite> sprite;
    bool alive = true;

public:
    virtual ~Entity() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void OnCollision(Entity* other) = 0;

    virtual void Render(sf::RenderWindow& window)
    {
        if (sprite.has_value())
            window.draw(*sprite);
    }

    sf::FloatRect getBounds() const
    {
        return sprite.has_value() ? sprite->getGlobalBounds() : sf::FloatRect();
    }
    
    bool isAlive() const
    {
        return alive;
    }
    
};
