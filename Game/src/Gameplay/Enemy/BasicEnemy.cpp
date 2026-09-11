#include "Gameplay/Enemy/BasicEnemy.h"

BasicEnemy::BasicEnemy(sf::Vector2f position)
    : Enemy(position, 150.f, 20)
{
    shape.setFillColor(sf::Color::Red);

    setEnemyTexture(
        "entities/basic_enemy.png"
    );
}

void BasicEnemy::Update(float deltaTime)
{
    moveEnemy({
        0.f,
        speed * deltaTime
        });

    if (isOffScreen())
        alive = false;
}