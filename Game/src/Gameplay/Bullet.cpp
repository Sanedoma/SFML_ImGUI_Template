#include "Gameplay/Bullet.h"

#include "Core/AssetManager.h"

Bullet::Bullet(sf::Vector2f startPosition)
    : position(startPosition)
{
    shape.setSize({ 6.f, 16.f });
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);

    const sf::Texture& texture =
        AssetManager::instance().texture(
            "entities/player_bullet.png"
        );

    sprite.emplace(texture);

    sf::Vector2u textureSize =
        texture.getSize();

    float scaleX =
        6.f / static_cast<float>(textureSize.x);

    float scaleY =
        16.f / static_cast<float>(textureSize.y);

    sprite->setScale({
        scaleX,
        scaleY
        });

    sprite->setPosition(position);
}

void Bullet::Update(float deltaTime)
{
    position.y -= speed * deltaTime;

    shape.setPosition(position);

    if (sprite.has_value())
        sprite->setPosition(position);

    if (isOffScreen())
        alive = false;
}

void Bullet::Render(sf::RenderWindow& window)
{
    if (sprite.has_value())
        window.draw(*sprite);
    else
        window.draw(shape);
}

void Bullet::OnCollision(Entity* other)
{
    if (other->getType() == EntityType::ENEMY)
        alive = false;
}

sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}

EntityType Bullet::getType() const
{
    return EntityType::BULLET;
}

bool Bullet::isOffScreen() const
{
    sf::FloatRect bounds =
        shape.getGlobalBounds();

    return bounds.position.y
        + bounds.size.y < 0.f;
}