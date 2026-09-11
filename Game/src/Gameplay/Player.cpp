#include "Gameplay/Player.h"

#include <SFML/Window/Keyboard.hpp>

#include "Core/AssetManager.h"
#include "Core/Config.h"
#include "Gameplay/Bullet.h"
#include "Gameplay/Obstacle.h"

Player::Player()
{
    fallback.setSize({
        Size,
        Size
        });

    fallback.setFillColor(
        sf::Color::Green
    );

    fallback.setPosition(position);

    const sf::Texture& playerTexture =
        AssetManager::instance().texture(
            "entities/player.png"
        );

    sprite.emplace(playerTexture);

    sf::Vector2u textureSize =
        playerTexture.getSize();

    float scaleX =
        Size / static_cast<float>(textureSize.x);

    float scaleY =
        Size / static_cast<float>(textureSize.y);

    sprite->setScale({
        scaleX,
        scaleY
        });

    sprite->setPosition(position);

    hasSprite = true;
}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement({
        0.f,
        0.f
        });

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::Left))
    {
        movement.x -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::Right))
    {
        movement.x += 1.f;
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::Up))
    {
        movement.y -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::Down))
    {
        movement.y += 1.f;
    }

    position += movement * speed * deltaTime;

    float width =
        static_cast<float>(cfg::WindowWidth);

    float height =
        static_cast<float>(cfg::WindowHeight);

    if (position.x < 0.f)
        position.x = 0.f;

    if (position.y < 0.f)
        position.y = 0.f;

    if (position.x > width - Size)
        position.x = width - Size;

    if (position.y > height - Size)
        position.y = height - Size;

    if (shootCooldown > 0.f)
        shootCooldown -= deltaTime;

    if (invulnerable)
    {
        invulnerabilityTime -= deltaTime;

        if (invulnerabilityTime <= 0.f)
            invulnerable = false;
    }

    if (speedBoosted)
    {
        speedBoostTimer -= deltaTime;

        if (speedBoostTimer <= 0.f)
        {
            speedBoosted = false;
            speed = baseSpeed;
        }
    }

    if (damageBoosted)
    {
        damageBoostTimer -= deltaTime;

        if (damageBoostTimer <= 0.f)
        {
            damageBoosted = false;
            currentDamage = baseDamage;
        }
    }

    fallback.setPosition(position);

    if (hasSprite)
        sprite->setPosition(position);
}

void Player::Render(sf::RenderWindow& window)
{
    if (hasSprite)
        window.draw(sprite.value());
    else
        window.draw(fallback);
}

std::unique_ptr<Bullet> Player::TryShoot()
{
    bool wantsToShoot =
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::Key::Space
        );

    if (wantsToShoot && shootCooldown <= 0.f)
    {
        shootCooldown = fireRate;

        sf::Vector2f bulletPos{
            position.x + Size / 2.f - 3.f,
            position.y - 2.f
        };

        return std::make_unique<Bullet>(
            bulletPos
        );
    }

    return nullptr;
}

void Player::OnCollision(Entity* other)
{
    if (
        other->getType() == EntityType::ENEMY
        ||
        other->getType() == EntityType::ENEMY_BULLET
        )
    {
        TakeDammage(1);
    }
    else if (
        other->getType() == EntityType::BUFF
        )
    {
        Buff* buff =
            static_cast<Buff*>(other);

        ApplyBuff(
            buff->getBuffType()
        );
    }
    else if (other->getType() == EntityType::OBSTACLE)
    {
        // Les debris minuscules (0 degat) ne doivent pas gaspiller le
        // bouclier ni declencher l'invulnerabilite.
        Obstacle* obstacle = static_cast<Obstacle*>(other);
        if (obstacle->getContactDamage() > 0)
            TakeDammage(obstacle->getContactDamage());
    }
}

sf::FloatRect Player::getBounds() const
{
    // Le rectangle vert sert toujours de hitbox.
    return fallback.getGlobalBounds();
}

EntityType Player::getType() const
{
    return EntityType::PLAYER;
}

void Player::TakeDammage(int amount)
{
    if (invulnerable)
        return;

    if (hasShield)
    {
        hasShield = false;

        invulnerable = true;

        invulnerabilityTime =
            invulnerabilityDuration / 2.f;

        return;
    }

    health -= amount;

    invulnerable = true;

    invulnerabilityTime =
        invulnerabilityDuration;

    if (health <= 0)
    {
        health = 0;
        alive = false;
    }
}

void Player::ApplyBuff(BuffType type)
{
    switch (type)
    {
    case BuffType::ExtraLife:
        health += 1;
        break;

    case BuffType::Shield:
        hasShield = true;
        break;

    case BuffType::Speed:
        speed = baseSpeed * 2.f;
        speedBoosted = true;
        speedBoostTimer = speedBoostDuration;
        break;

    case BuffType::Dammage:
        currentDamage = baseDamage * 2;
        damageBoosted = true;
        damageBoostTimer = damageBoostDuration;
        break;
    }
}