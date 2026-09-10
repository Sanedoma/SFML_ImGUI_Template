#include "World/Hud.h"

#include <algorithm>
#include <string>

#include "Core/AssetManager.h"
#include "Core/Config.h"
#include "Gameplay/Player.h"

namespace
{
	constexpr sf::Vector2f BarPosition{ 16.f, 16.f };
	constexpr sf::Vector2f BarSize{ 220.f, 26.f };
	constexpr float DigitScale = 1.6f;
	constexpr float DigitSpacing = 2.f;
	constexpr float ScreenPadding = 16.f;
}

Hud::Hud()
{
	AssetManager& assets = AssetManager::instance();
	barTrack = &assets.texture("hud/bar_track.png");
	barGreen = &assets.texture("hud/bar_fill_green.png");
	barYellow = &assets.texture("hud/bar_fill_yellow.png");
	barRed = &assets.texture("hud/bar_fill_red.png");
	barOver = &assets.texture("hud/bar_fill_over.png");

	for (int i = 0; i < 10; ++i)
		digits[i] = &assets.texture("hud/digit_" + std::to_string(i) + ".png");
}

void Hud::Update(const Player& player, int currentScore)
{
	health = player.getHealth();
	maxHealth = std::max(1, player.getMaxHealth());
	score = currentScore;
}

const sf::Texture& Hud::fillTextureFor(float ratio) const
{
	if (ratio > 0.6f) return *barGreen;
	if (ratio > 0.3f) return *barYellow;
	return *barRed;
}

void Hud::drawBarFill(sf::RenderWindow& window, const sf::Texture& texture, float ratio) const
{
	ratio = std::clamp(ratio, 0.f, 1.f);
	if (ratio <= 0.f)
		return;

	const sf::Vector2f textureSize(texture.getSize());
	sf::Sprite fill(texture);
	fill.setTextureRect({ { 0, 0 },
	                      { static_cast<int>(textureSize.x * ratio), static_cast<int>(textureSize.y) } });
	fill.setPosition(BarPosition);
	fill.setScale({ BarSize.x / textureSize.x, BarSize.y / textureSize.y });
	window.draw(fill);
}

void Hud::Render(sf::RenderWindow& window)
{
	// --- barre de vie ---
	{
		const sf::Vector2f trackSize(barTrack->getSize());
		sf::Sprite track(*barTrack);
		track.setPosition(BarPosition);
		track.setScale({ BarSize.x / trackSize.x, BarSize.y / trackSize.y });
		window.draw(track);
	}

	const float ratio = static_cast<float>(health) / static_cast<float>(maxHealth);
	drawBarFill(window, fillTextureFor(ratio), ratio);

	if (health > maxHealth)
		drawBarFill(window, *barOver, static_cast<float>(health - maxHealth) / static_cast<float>(maxHealth));

	// --- score, aligne a droite ---
	const std::string text = std::to_string(score);

	float totalWidth = 0.f;
	for (char c : text)
		totalWidth += static_cast<float>(digits[c - '0']->getSize().x) * DigitScale + DigitSpacing;
	totalWidth -= DigitSpacing;

	float x = static_cast<float>(cfg::WindowWidth) - ScreenPadding - totalWidth;
	for (char c : text)
	{
		const sf::Texture& glyph = *digits[c - '0'];
		sf::Sprite sprite(glyph);
		sprite.setPosition({ x, ScreenPadding });
		sprite.setScale({ DigitScale, DigitScale });
		window.draw(sprite);
		x += static_cast<float>(glyph.getSize().x) * DigitScale + DigitSpacing;
	}
}
