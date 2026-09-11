#include "Gameplay/Buff.h"

#include <string>

#include "Core/AssetManager.h"
#include "Core/Config.h"

Buff::Buff(
    sf::Vector2f startPosition,
    BuffType buffType
)
    : position(startPosition),
    type(buffType)
{
    shape.setSize({ 24.f, 24.f });
    shape.setPosition(position);

    std::string texturePath;

    switch (type)
    {
    case BuffType::Speed:
        shape.setFillColor(sf::Color::Cyan);
        texturePath = "entities/speed_buff.png";
        break;

    case BuffType::Dammage:
        shape.setFillColor(sf::Color::Magenta);
        texturePath = "entities/damage_buff.png";
        break;

    case BuffType::Shield:
        shape.setFillColor(sf::Color::Blue);
        texturePath = "entities/shield_buff.png";
        break;

    case BuffType::ExtraLife:
        shape.setFillColor(sf::Color::Green);
        texturePath = "entities/extra_life_buff.png";
        break;
    }

    const sf::Texture& texture =
        AssetManager::instance().texture(
            texturePath
        );

    sprite.emplace(texture);

    sf::Vector2u textureSize =
        texture.getSize();

    float scaleX =
        24.f / static_cast<float>(textureSize.x);

    float scaleY =
        24.f / static_cast<float>(textureSize.y);

    sprite->setScale({
        scaleX,
        scaleY
        });

    sprite->setPosition(position);
}

void Buff::Update(float deltaTime)
{
    position.y += speed * deltaTime;

    shape.setPosition(position);

    if (sprite.has_value())
        sprite->setPosition(position);

    if (isOffScreen())
        alive = false;
}

void Buff::Render(sf::RenderWindow& window)
{
    if (sprite.has_value())
        window.draw(*sprite);
    else
        window.draw(shape);
}

void Buff::OnCollision(Entity* other)
{
    if (other->getType() == EntityType::PLAYER)
        alive = false;
}

sf::FloatRect Buff::getBounds() const
{
    return shape.getGlobalBounds();
}

EntityType Buff::getType() const
{
    return EntityType::BUFF;
}

bool Buff::isOffScreen() const
{
    sf::FloatRect bounds =
        shape.getGlobalBounds();

    return bounds.position.y
        + bounds.size.y
        > static_cast<float>(cfg::WindowHeight);
}