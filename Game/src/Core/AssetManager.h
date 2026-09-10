#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

// Central texture and font cache. Paths are relative to cfg::AssetsRoot.
// A missing texture resolves to a magenta placeholder so the game still runs.
class AssetManager
{
public:
	static AssetManager& instance();

	const sf::Texture& texture(const std::string& path);
	const sf::Font& font(const std::string& path);

	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

private:
	AssetManager() = default;

	const sf::Texture& fallbackTexture();

	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
	sf::Texture fallback;
	bool fallbackLoaded = false;
};
