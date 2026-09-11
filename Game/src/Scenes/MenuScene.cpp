#include "Scenes/MenuScene.h"

#include <filesystem>
#include <memory>
#include <string>

#include "ImGui/imgui.h"

#include "Core/Config.h"
#include "Core/Game.h"
#include "Scenes/PlayScene.h"
#include "Scenes/SettingsScene.h"

void MenuScene::Render(sf::RenderWindow& window)
{
	window.clear(sf::Color(10, 12, 24));

	const ImVec2 display = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos({ display.x * 0.5f, display.y * 0.5f }, ImGuiCond_Always, { 0.5f, 0.5f });
	ImGui::Begin("Shoot'em Up", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Jouer", { 160.f, 0.f }))
		game.scenes().replace(std::make_unique<PlayScene>(game));

	const std::string levelsDir = std::string(cfg::AssetsRoot) + "levels";
	if (std::filesystem::exists(levelsDir))
	{
		for (const auto& entry : std::filesystem::directory_iterator(levelsDir))
		{
			if (entry.path().extension() != ".txt")
				continue;

			const std::string filename = entry.path().filename().string();
			if (filename == "level1.txt")
				continue; // deja couvert par "Jouer"

			if (ImGui::Button(filename.c_str(), { 160.f, 0.f }))
				game.scenes().replace(std::make_unique<PlayScene>(game, "levels/" + filename));
		}
	}

	if (ImGui::Button("Options", { 160.f, 0.f }))
		game.scenes().push(std::make_unique<SettingsScene>(game));

	if (ImGui::Button("Quitter", { 160.f, 0.f }))
		game.window().close();

	ImGui::End();
}
