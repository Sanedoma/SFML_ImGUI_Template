#pragma once
#include <memory>
#include <random>
#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

class Entity;

// Charge un niveau depuis un fichier texte (grille de symboles, une ligne =
// une vague) et distribue les entites correspondantes au fil du temps.
// Voir Assets/levels/*.txt pour des exemples de format.
class LevelLoader
{
public:
	explicit LevelLoader(const std::string& path);

	// A appeler chaque frame ; renvoie les entites dont c'est l'heure de spawn.
	std::vector<std::unique_ptr<Entity>> Update(float deltaTime);

	// Vrai une fois toutes les lignes du fichier distribuees.
	bool isFinished() const;

private:
	struct SpawnEvent
	{
		float time;
		float x;
		char symbol;
	};

	void parse(const std::string& path);
	std::unique_ptr<Entity> spawnFor(char symbol, sf::Vector2f position);

	std::vector<SpawnEvent> events;
	std::size_t nextEvent = 0;
	float elapsed = 0.f;

	std::mt19937 rng{ std::random_device{}() };
};
