#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

#include "Bullet.h"
#include "Buff.h"

#include "../Core/Entity.h"

class Player : public Entity
{
protected:
    sf::Texture texture;
    sf::RectangleShape fallback;        // rectangle vert sinon
    bool hasSprite = false;
    sf::Vector2f position = { 375.f, 500.f };


    // Tir
	float shootCooldown = 0.f; //temps restant avant le prochaint tire
	float fireRate = 0.5f; // temps entre deux tirs (en secondes)
    
    // Santé 
    int health = 3; 
	bool invulnerable = false; 
    float invulnerabilityTime = 0.f;
	const float invulnerabilityDuration = 4.f;
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

public:
    Player(){
        // Rectangle de secours (toujours prêt)
        fallback.setSize({ 50.f, 50.f });
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

    void Update(float deltaTime) override{
        sf::Vector2f movement({ 0.f, 0.f });

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  movement.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) movement.x += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    movement.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  movement.y += 1.f;

        position += movement * speed * deltaTime;

		// On empêche le joueur de sortir de l'écran
        const float sizeX = 50.f;
		const float sizeY = 50.f;

        if (position.x < 0.f)            position.x = 0.f;
        if (position.y < 0.f)            position.y = 0.f;
        if (position.x > 800.f - sizeX)  position.x = 800.f - sizeX;
        if (position.y > 600.f - sizeY)  position.y = 600.f - sizeY;

		//Décompte du cooldown de tir
        if(shootCooldown > 0.f)
			shootCooldown -= deltaTime;
		//Décompte du temps d'invulnérabilité 
        if (invulnerable) {
			invulnerabilityTime -= deltaTime;
			if (invulnerabilityTime <= 0.f) {
				invulnerable = false;
			}
        }
		// Décompte du temps de boost de vitesse
        if (speedBoosted) {
			speedBoostTimer -= deltaTime;
            if (speedBoostTimer <= 0.f) {
				speedBoosted = false;
				speed = baseSpeed;
            }
        }

		// Décompte du temps de boost de dégâts
        if (damageBoosted) {
            damageBoostTimer -= deltaTime;
            if (damageBoostTimer <= 0.f) {
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

    void Render(sf::RenderWindow& window) override{
        if (hasSprite) window.draw(sprite.value());
        else           window.draw(fallback);
    }

    sf::Vector2f getPosition() const { return position; }

    std::optional<Bullet> TryShoot() {
		bool wantsToShoot = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

		if (wantsToShoot && shootCooldown <= 0.f) {
            shootCooldown = fireRate;

            sf::Vector2f bulletPos = {
                position.x + 25.f - 3.f,
                position.y - 2.f
            };
			return Bullet(bulletPos);
		}

		return std::nullopt;
    }

	void OnCollision(Entity* other) override {
		// Ici, on pourrait gérer la collision avec d'autres entités
		// Par exemple, si le joueur touche un ennemi ou un projectile ennemi
	}

	sf::FloatRect getBounds() const {
		if (hasSprite) return sprite->getGlobalBounds();
		return fallback.getGlobalBounds();
	}

	void TakeDammage(int amount) {
        if (invulnerable) return;

        if (hasShield) {
			hasShield = false; // Le bouclier absorbe les dégâts
            invulnerable = true;
			invulnerabilityTime = invulnerabilityDuration / 2.0f;
            return;
        }

        health -= amount;
        invulnerable = true;
		invulnerabilityTime = invulnerabilityDuration;
        if (health < 0) health = 0;
	}

    void ApplyBuff(BuffType type){
        switch (type) {
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

    int getHealth() const { return health; }
	bool isAlive() const { return health > 0; }
    bool getHasShield() const { return hasShield; }
    float getSpeed() const { return speed; }
    int getCurrentDamage() const { return currentDamage; }
};
