#include "Gameplay/Enemy/ShooterEnemy.h"

namespace
{
    constexpr float EntrySpeed = 80.f;
    constexpr float HoldY = 80.f; // position ou l'ennemi s'arrete pour tirer
}

ShooterEnemy::ShooterEnemy(sf::Vector2f position)
    : Enemy(position, EntrySpeed, 3)
{
    shape.setFillColor(sf::Color::Yellow);

    setEnemyTexture(
        "entities/shooter_enemy.png"
    );

    if (position.y >= HoldY)
        inPosition = true;
}

void ShooterEnemy::Update(float deltaTime)
{
    // L'ennemi descend jusqu'a sa position de tir
    if (!inPosition)
    {
        float nextY =
            shape.getPosition().y
            + speed * deltaTime;

        if (nextY >= HoldY)
        {
            float distanceToHold =
                HoldY - shape.getPosition().y;

            moveEnemy({
                0.f,
                distanceToHold
                });

            inPosition = true;
        }
        else
        {
            moveEnemy({
                0.f,
                speed * deltaTime
                });
        }

        return;
    }

    // Une fois en position, il commence a tirer
    shootTimer += deltaTime;

    if (shootTimer >= shootCooldown)
    {
        wantsToShoot = true;
        shootTimer = 0.f;
    }
}

bool ShooterEnemy::consumeShootRequest()
{
    if (wantsToShoot)
    {
        wantsToShoot = false;
        return true;
    }

    return false;
}