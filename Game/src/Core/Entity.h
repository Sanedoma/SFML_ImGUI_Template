#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

enum class EntityType
{
	PLAYER,
	ENEMY,
	BULLET,
	BUFF,
	OBSTACLE
};

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

    virtual sf::FloatRect getBounds() const
    {
        return sprite.has_value() ? sprite->getGlobalBounds() : sf::FloatRect();
    }
    
	virtual EntityType getType() const = 0;

    bool isAlive() const { return alive; }
    
};
