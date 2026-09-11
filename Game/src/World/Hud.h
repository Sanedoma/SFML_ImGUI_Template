#pragma once
#include <array>

#include <SFML/Graphics.hpp>

class Player;

// HUD in-game : barre de vie (haut-gauche) et score (haut-droite),
// dessine en coordonnees ecran par-dessus la scene.
class Hud
{
public:
	Hud();

	void Update(const Player& player, int score);
	void Render(sf::RenderWindow& window);

private:
	const sf::Texture& fillTextureFor(float ratio) const;
	void drawBarFill(sf::RenderWindow& window, const sf::Texture& texture, float ratio) const;

	const sf::Texture* barTrack = nullptr;
	const sf::Texture* barGreen = nullptr;
	const sf::Texture* barYellow = nullptr;
	const sf::Texture* barRed = nullptr;
	const sf::Texture* barOver = nullptr;
	std::array<const sf::Texture*, 10> digits{};

	int health = 0;
	int maxHealth = 1;
	int score = 0;
};
