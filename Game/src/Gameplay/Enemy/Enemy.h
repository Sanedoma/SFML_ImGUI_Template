#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Core/Entity.h"

class Enemy : public Entity
{
public:
    Enemy(sf::Vector2f position, float speed, int health);

    void Render(sf::RenderWindow& window) override;
    void OnCollision(Entity* other) override;

    sf::FloatRect getBounds() const override;
    EntityType getType() const override;

    virtual void ReactToPlayer(
        sf::Vector2f playerPosition,
        float deltaTime
    );

    virtual bool consumeShootRequest();

    void takeDamage(int damage);
    void kill();

    sf::Vector2f getPosition() const;

    bool wasKilledByBullet() const
    {
        return killedByBullet;
    }

protected:
    bool isOffScreen() const;

    void setEnemyTexture(const std::string& texturePath);
    void moveEnemy(sf::Vector2f movement);

    sf::RectangleShape shape;

    float speed;
    int health;

    bool killedByBullet = false;
};