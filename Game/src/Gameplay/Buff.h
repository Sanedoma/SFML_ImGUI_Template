#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Entity.h"

enum class BuffType
{
    Speed,
    Dammage,
    Shield,
    ExtraLife
};

class Buff : public Entity
{
public:
    Buff(sf::Vector2f position, BuffType type);

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnCollision(Entity* other) override;

    sf::FloatRect getBounds() const override;
    EntityType getType() const override;

    BuffType getBuffType() const
    {
        return type;
    }

    sf::Vector2f getPosition() const
    {
        return position;
    }

private:
    bool isOffScreen() const;

    sf::RectangleShape shape;
    sf::Vector2f position;

    float speed = 100.f;
    BuffType type;
};