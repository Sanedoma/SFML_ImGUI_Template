#pragma once

#include "Gameplay/Enemy/Enemy.h"

class ExplosiveEnemy : public Enemy
{
public:
    ExplosiveEnemy(sf::Vector2f position);

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    void ReactToPlayer(
        sf::Vector2f playerPosition,
        float deltaTime
    ) override;

    bool hasExploded() const { return exploded; }
    float getExplosionRadius() const { return explosionRadius; }

private:
    void rotateTowardPlayer(sf::Vector2f playerPosition);
    void updateBlink(float deltaTime);

    float triggerDistance = 70.f;
    float explosionRadius = 75.f;

    float explosionTimer = 0.f;
    float explosionDelay = 0.8f;

    bool preparingExplosion = false;
    bool exploded = false;

    float blinkTimer = 0.f;
    float blinkInterval = 0.12f;
    bool blinkVisible = true;

    bool showingExplosion = false;
    float explosionEffectTimer = 0.f;
    float explosionEffectDuration = 0.25f;

    sf::CircleShape explosionCircle;
};