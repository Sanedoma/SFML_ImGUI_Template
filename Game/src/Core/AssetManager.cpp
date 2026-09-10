#include "Core/AssetManager.h"

#include <iostream>

#include "Core/Config.h"

AssetManager& AssetManager::instance()
{
	static AssetManager manager;
	return manager;
}

const sf::Texture& AssetManager::texture(const std::string& path)
{
	if (const auto it = textures.find(path); it != textures.end())
		return it->second;

	sf::Texture loaded;
	if (!loaded.loadFromFile(cfg::AssetsRoot + path))
	{
		std::cerr << "AssetManager: missing texture " << path << '\n';
		return fallbackTexture();
	}

	return textures.emplace(path, std::move(loaded)).first->second;
}

const sf::Font& AssetManager::font(const std::string& path)
{
	if (const auto it = fonts.find(path); it != fonts.end())
		return it->second;

	sf::Font loaded;
	if (!loaded.openFromFile(cfg::AssetsRoot + path))
		std::cerr << "AssetManager: missing font " << path << '\n';

	return fonts.emplace(path, std::move(loaded)).first->second;
}

const sf::Texture& AssetManager::fallbackTexture()
{
	if (!fallbackLoaded)
	{
		const sf::Image image({ 8, 8 }, sf::Color::Magenta);
		fallbackLoaded = fallback.loadFromImage(image);
	}
	return fallback;
}
