#include "World/LevelLoader.h"

#include <fstream>
#include <iostream>

#include "Core/Config.h"
#include "Core/Entity.h"
#include "Gameplay/Enemy/BasicEnemy.h"
#include "Gameplay/Enemy/ExplosiveEnemy.h"
#include "Gameplay/Enemy/ShooterEnemy.h"
#include "Gameplay/Obstacle.h"

LevelLoader::LevelLoader(const std::string& path)
{
	parse(path);
}

void LevelLoader::parse(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "LevelLoader: impossible d'ouvrir " << path << '\n';
		return;
	}

	std::string line;
	int row = 0;
	while (std::getline(file, line))
	{
		if (!line.empty() && line.back() == '\r')
			line.pop_back();

		for (int col = 0; col < cfg::LevelColumns; ++col)
		{
			const char symbol = col < static_cast<int>(line.size()) ? line[col] : '.';
			if (symbol == '.')
				continue;

			if (symbol != 'E' && symbol != 'T' && symbol != 'X' && symbol != '#')
			{
				std::cerr << "LevelLoader: symbole inconnu '" << symbol << "' a la ligne " << row << '\n';
				continue;
			}

			const float x = static_cast<float>(col) * cfg::LevelColumnWidth + cfg::LevelColumnWidth / 2.f;
			events.push_back({ static_cast<float>(row) * cfg::LevelRowInterval, x, symbol });
		}
		++row;
	}
}

std::vector<std::unique_ptr<Entity>> LevelLoader::Update(float deltaTime)
{
	elapsed += deltaTime;

	std::vector<std::unique_ptr<Entity>> spawned;
	while (nextEvent < events.size() && events[nextEvent].time <= elapsed)
	{
		if (auto entity = spawnFor(events[nextEvent].symbol, { events[nextEvent].x, -60.f }))
			spawned.push_back(std::move(entity));
		++nextEvent;
	}
	return spawned;
}

bool LevelLoader::isFinished() const
{
	return nextEvent >= events.size();
}

std::unique_ptr<Entity> LevelLoader::spawnFor(char symbol, sf::Vector2f position)
{
	switch (symbol)
	{
	case 'E':
		return std::make_unique<BasicEnemy>(position);
	case 'T':
		return std::make_unique<ShooterEnemy>(position);
	case 'X':
		return std::make_unique<ExplosiveEnemy>(position);
	case '#':
	{
		std::uniform_int_distribution<int> sizeDist(0, 2);
		return std::make_unique<Obstacle>(position, static_cast<ObstacleSize>(sizeDist(rng)));
	}
	default:
		return nullptr;
	}
}
