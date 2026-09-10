#pragma once
#include <cstdint>
#include <optional>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

// Fond spatial defilant. Une tuile repetee en couche lointaine, plus deux
// couches d'etoiles a des vitesses differentes pour l'effet de parallaxe.
class Background
{
public:
	Background();

	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);

private:
	struct Star
	{
		sf::Sprite sprite;
		float speed;

		Star(const sf::Texture& texture, float speed) : sprite(texture), speed(speed) {}
	};

	void addStarLayer(const sf::Texture& texture, int count, float speed, float scale, std::uint8_t alpha);

	sf::Texture tileTexture;
	std::optional<sf::Sprite> tile;
	float tileSpeed;
	float scrollY = 0.f;

	std::vector<Star> stars;
	std::mt19937 rng;
};
