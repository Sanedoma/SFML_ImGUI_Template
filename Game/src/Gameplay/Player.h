#pragma once
#include <memory>

#include <SFML/Graphics.hpp>

#include "Core/Entity.h"
#include "Gameplay/Buff.h"

class Bullet;
class Obstacle;

class Player : public Entity
{
public:
    Player();

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnCollision(Entity* other) override;
    sf::FloatRect getBounds() const override;
    EntityType getType() const override;

    std::unique_ptr<Bullet> TryShoot();

    void TakeDammage(int amount);
    void ApplyBuff(BuffType type);

    sf::Vector2f getPosition() const { return position; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return baseMaxHealth; }
    bool getHasShield() const { return hasShield; }
    float getSpeed() const { return speed; }
    int getCurrentDamage() const { return currentDamage; }

protected:
    sf::Texture texture;
    sf::RectangleShape fallback;        // rectangle vert sinon
    bool hasSprite = false;
    sf::Vector2f position = { 375.f, 500.f };
    static constexpr float Size = 50.f;

    // Tir
    float shootCooldown = 0.f; //temps restant avant le prochaint tire
    float fireRate = 0.5f; // temps entre deux tirs (en secondes)

    // Santé
    static constexpr int baseMaxHealth = 3;
    int health = baseMaxHealth;
    bool invulnerable = false;
    float invulnerabilityTime = 0.f;
    const float invulnerabilityDuration = 1.f;
    bool hasShield = false;

    // Mouvement
    float speed = 300.f;
    const float baseSpeed = 300.f;   // valeur de référence, ne change JAMAIS
    bool speedBoosted = false;
    float speedBoostTimer = 0.f;
    const float speedBoostDuration = 5.f;

    // Dégâts
    const int baseDamage = 1;        // dégâts de base d'une balle
    int currentDamage = 1;
    bool damageBoosted = false;
    float damageBoostTimer = 0.f;
    const float damageBoostDuration = 5.f;
};
