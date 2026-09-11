#pragma once

namespace cfg
{
	constexpr unsigned int WindowWidth = 800;
	constexpr unsigned int WindowHeight = 600;

	constexpr float ScrollSpeed = 120.f;

	constexpr const char* WindowTitle = "Shoot'em Up";
	constexpr const char* AssetsRoot = "Assets/";

	constexpr int LevelColumns = 20;
	constexpr float LevelColumnWidth = static_cast<float>(WindowWidth) / static_cast<float>(LevelColumns);
	constexpr float LevelRowInterval = 1.0f; // secondes entre deux lignes du fichier de niveau
}
