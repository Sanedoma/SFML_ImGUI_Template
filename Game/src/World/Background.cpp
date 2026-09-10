#include "World/Background.h"

#include <string>

#include "Core/AssetManager.h"
#include "Core/Config.h"

namespace
{
	constexpr int TileSize = 256;
	constexpr float Margin = 40.f;
}

Background::Background()
	: tileSpeed(cfg::ScrollSpeed * 0.15f), rng(1337)
{
	if (tileTexture.loadFromFile(std::string(cfg::AssetsRoot) + "background/space_purple.png"))
		tileTexture.setRepeated(true);
	tile.emplace(tileTexture);
	tile->setTextureRect({ { 0, 0 }, { static_cast<int>(cfg::WindowWidth), static_cast<int>(cfg::WindowHeight) } });

	addStarLayer(AssetManager::instance().texture("stars/star_dim.png"), 40, cfg::ScrollSpeed * 0.4f, 0.6f, 140);
	addStarLayer(AssetManager::instance().texture("stars/star_bright.png"), 20, cfg::ScrollSpeed * 0.8f, 1.0f, 230);
}

void Background::addStarLayer(const sf::Texture& texture, int count, float speed, float scale, std::uint8_t alpha)
{
	std::uniform_real_distribution<float> xDist(0.f, static_cast<float>(cfg::WindowWidth));
	std::uniform_real_distribution<float> yDist(0.f, static_cast<float>(cfg::WindowHeight));

	for (int i = 0; i < count; ++i)
	{
		Star star(texture, speed);
		star.sprite.setPosition({ xDist(rng), yDist(rng) });
		star.sprite.setScale({ scale, scale });
		star.sprite.setColor(sf::Color(255, 255, 255, alpha));
		stars.push_back(std::move(star));
	}
}

void Background::Update(float deltaTime)
{
	scrollY += tileSpeed * deltaTime;
	if (scrollY >= TileSize)
		scrollY -= TileSize;
	tile->setTextureRect({ { 0, -static_cast<int>(scrollY) },
	                       { static_cast<int>(cfg::WindowWidth), static_cast<int>(cfg::WindowHeight) } });

	const float wrapDistance = cfg::WindowHeight + 2.f * Margin;
	std::uniform_real_distribution<float> xDist(0.f, static_cast<float>(cfg::WindowWidth));

	for (Star& star : stars)
	{
		star.sprite.move({ 0.f, star.speed * deltaTime });
		if (star.sprite.getPosition().y > cfg::WindowHeight + Margin)
			star.sprite.setPosition({ xDist(rng), star.sprite.getPosition().y - wrapDistance });
	}
}

void Background::Render(sf::RenderWindow& window)
{
	window.draw(*tile);
	for (const Star& star : stars)
		window.draw(star.sprite);
}
