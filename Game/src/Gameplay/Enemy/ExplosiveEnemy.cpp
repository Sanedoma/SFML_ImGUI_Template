#include "Gameplay/Enemy/ExplosiveEnemy.h"

#include <cmath>

ExplosiveEnemy::ExplosiveEnemy(sf::Vector2f position)
    : Enemy(position, 120.f, 10)
{
    setEnemyTexture("entities/explosive_enemy.png");

    if (sprite.has_value())
    {
        sf::FloatRect bounds = sprite->getLocalBounds();

        sprite->setOrigin({
            bounds.size.x / 2.f,
            bounds.size.y / 2.f
            });

        sprite->setPosition({
            shape.getPosition().x + 20.f,
            shape.getPosition().y + 20.f
            });
    }

    explosionCircle.setRadius(explosionRadius);
    explosionCircle.setOrigin({
        explosionRadius,
        explosionRadius
        });

    explosionCircle.setFillColor(
        sf::Color(255, 140, 0, 90)
    );
}

void ExplosiveEnemy::Update(float deltaTime)
{
    if (exploded)
        exploded = false;

    if (preparingExplosion)
    {
        explosionTimer += deltaTime;
        updateBlink(deltaTime);

        if (explosionTimer >= explosionDelay)
        {
            preparingExplosion = false;
            exploded = true;
            showingExplosion = true;
            explosionEffectTimer = 0.f;

            explosionCircle.setPosition({
                shape.getPosition().x + 20.f,
                shape.getPosition().y + 20.f
                });
        }
    }

    if (showingExplosion)
    {
        explosionEffectTimer += deltaTime;

        if (explosionEffectTimer >= explosionEffectDuration)
        {
            showingExplosion = false;
            alive = false;
        }
    }
}

void ExplosiveEnemy::Render(sf::RenderWindow& window)
{
    if (showingExplosion)
        window.draw(explosionCircle);
    else
        Enemy::Render(window);
}

void ExplosiveEnemy::ReactToPlayer(
    sf::Vector2f playerPosition,
    float deltaTime
)
{
    rotateTowardPlayer(playerPosition);

    if (preparingExplosion || showingExplosion)
        return;

    sf::Vector2f enemyCenter =
        shape.getPosition() + sf::Vector2f{ 20.f, 20.f };

    sf::Vector2f playerCenter =
        playerPosition + sf::Vector2f{ 25.f, 25.f };

    sf::Vector2f direction =
        playerCenter - enemyCenter;

    float distance = std::sqrt(
        direction.x * direction.x +
        direction.y * direction.y
    );

    if (distance <= triggerDistance)
    {
        preparingExplosion = true;
        explosionTimer = 0.f;
        blinkTimer = 0.f;
        return;
    }

    if (distance > 0.f)
    {
        direction /= distance;

        moveEnemy(
            direction * speed * deltaTime
        );
    }
}

void ExplosiveEnemy::rotateTowardPlayer(
    sf::Vector2f playerPosition
)
{
    if (!sprite.has_value())
        return;

    sf::Vector2f enemyCenter =
        shape.getPosition() + sf::Vector2f{ 20.f, 20.f };

    sf::Vector2f playerCenter =
        playerPosition + sf::Vector2f{ 25.f, 25.f };

    sf::Vector2f direction =
        playerCenter - enemyCenter;

    float angle = std::atan2(
        direction.y,
        direction.x
    ) * 180.f / 3.14159265f;

    sprite->setRotation(
        sf::degrees(angle - 90.f)
    );
}

void ExplosiveEnemy::updateBlink(float deltaTime)
{
    blinkTimer += deltaTime;

    if (blinkTimer < blinkInterval)
        return;

    blinkTimer = 0.f;
    blinkVisible = !blinkVisible;

    if (!sprite.has_value())
        return;

    if (blinkVisible)
        sprite->setColor(sf::Color::White);
    else
        sprite->setColor(
            sf::Color(255, 255, 255, 60)
        );
}