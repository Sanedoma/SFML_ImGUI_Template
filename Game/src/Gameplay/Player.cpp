#include "Gameplay/Player.h"

#include <SFML/Window/Keyboard.hpp>

#include "Core/Config.h"
#include "Gameplay/Bullet.h"
#include "Gameplay/Obstacle.h"

Player::Player()
{
    // Rectangle de secours (toujours prêt)
    fallback.setSize({ Size, Size });
    fallback.setFillColor(sf::Color::Green);
    fallback.setPosition(position);

    // On tente de charger l'image ; si absente, on garde le rectangle
    if (texture.loadFromFile("assets/player.png"))
    {
        sprite.emplace(texture);
        sprite->setPosition(position);
        hasSprite = true;
    }
}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement({ 0.f, 0.f });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) movement.x += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  movement.y += 1.f;

    position += movement * speed * deltaTime;

    // On empêche le joueur de sortir de l'écran
    const float width = static_cast<float>(cfg::WindowWidth);
    const float height = static_cast<float>(cfg::WindowHeight);

    if (position.x < 0.f)              position.x = 0.f;
    if (position.y < 0.f)              position.y = 0.f;
    if (position.x > width - Size)     position.x = width - Size;
    if (position.y > height - Size)    position.y = height - Size;

    // Décompte du cooldown de tir
    if (shootCooldown > 0.f)
        shootCooldown -= deltaTime;

    // Décompte du temps d'invulnérabilité
    if (invulnerable)
    {
        invulnerabilityTime -= deltaTime;
        if (invulnerabilityTime <= 0.f)
            invulnerable = false;
    }

    // Décompte du temps de boost de vitesse
    if (speedBoosted)
    {
        speedBoostTimer -= deltaTime;
        if (speedBoostTimer <= 0.f)
        {
            speedBoosted = false;
            speed = baseSpeed;
        }
    }

    // Décompte du temps de boost de dégâts
    if (damageBoosted)
    {
        damageBoostTimer -= deltaTime;
        if (damageBoostTimer <= 0.f)
        {
            damageBoosted = false;
            currentDamage = baseDamage;
        }
    }

    // On répercute la position sur l'objet qu'on affiche
    if (hasSprite)
        sprite->setPosition(position);
    else
        fallback.setPosition(position);
}

void Player::Render(sf::RenderWindow& window)
{
    if (hasSprite) window.draw(sprite.value());
    else           window.draw(fallback);
}

std::unique_ptr<Bullet> Player::TryShoot()
{
    const bool wantsToShoot = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (wantsToShoot && shootCooldown <= 0.f)
    {
        shootCooldown = fireRate;

        const sf::Vector2f bulletPos = {
            position.x + Size / 2.f - 3.f,
            position.y - 2.f
        };
        return std::make_unique<Bullet>(bulletPos);
    }

    return nullptr;
}

void Player::OnCollision(Entity* other)
{
    if (other->getType() == EntityType::ENEMY ||
        other->getType() == EntityType::ENEMY_BULLET)
    {
        TakeDammage(1);
    }
    else if (other->getType() == EntityType::BUFF)
    {
        Buff* buff = static_cast<Buff*>(other);
        ApplyBuff(buff->getBuffType());
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
    if (hasSprite) return sprite->getGlobalBounds();
    return fallback.getGlobalBounds();
}

EntityType Player::getType() const
{
    return EntityType::PLAYER;
}

void Player::TakeDammage(int amount)
{
    if (invulnerable) return;

    if (hasShield)
    {
        hasShield = false; // Le bouclier absorbe les dégâts
        invulnerable = true;
        invulnerabilityTime = invulnerabilityDuration / 2.0f;
        return;
    }

    health -= amount;
    invulnerable = true;
    invulnerabilityTime = invulnerabilityDuration;
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
