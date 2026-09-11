#include "Gameplay/Enemy/EnemyBullet.h"

#include "Core/AssetManager.h"
#include "Core/Config.h"

EnemyBullet::EnemyBullet(sf::Vector2f position)
{
    shape.setSize({ 8.f, 18.f });
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);

    const sf::Texture& texture =
        AssetManager::instance().texture(
            "entities/enemy_bullet.png"
        );

    sprite.emplace(texture);

    sf::Vector2u textureSize =
        texture.getSize();

    float scaleX =
        8.f / static_cast<float>(textureSize.x);

    float scaleY =
        18.f / static_cast<float>(textureSize.y);

    sprite->setScale({
        scaleX,
        scaleY
        });

    sprite->setPosition(position);
}

void EnemyBullet::Update(float deltaTime)
{
    sf::Vector2f movement{
        0.f,
        speed * deltaTime
    };

    shape.move(movement);

    if (sprite.has_value())
        sprite->move(movement);

    if (shape.getPosition().y
        > static_cast<float>(cfg::WindowHeight))
    {
        alive = false;
    }
}

void EnemyBullet::Render(sf::RenderWindow& window)
{
    if (sprite.has_value())
        window.draw(*sprite);
    else
        window.draw(shape);
}

void EnemyBullet::OnCollision(Entity* other)
{
    if (other->getType() == EntityType::PLAYER)
        alive = false;
}

sf::FloatRect EnemyBullet::getBounds() const
{
    return shape.getGlobalBounds();
}

EntityType EnemyBullet::getType() const
{
    return EntityType::ENEMY_BULLET;
}