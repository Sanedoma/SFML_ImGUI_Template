#include "Scenes/LevelSelectScene.h"

#include <filesystem>
#include <memory>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "ImGui/imgui.h"

#include "Core/Config.h"
#include "Core/Game.h"
#include "Scenes/PlayScene.h"

void LevelSelectScene::handleEvent(const sf::Event& event)
{
	const auto* key = event.getIf<sf::Event::KeyPressed>();
	if (key && key->code == sf::Keyboard::Key::Escape)
		game.scenes().pop();
}

void LevelSelectScene::Render(sf::RenderWindow& window)
{
	sf::RectangleShape dim(sf::Vector2f(window.getSize()));
	dim.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(dim);

	const ImVec2 display = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos({ display.x * 0.5f, display.y * 0.5f }, ImGuiCond_Always, { 0.5f, 0.5f });
	ImGui::Begin("Niveaux", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize);

	const std::string levelsDir = std::string(cfg::AssetsRoot) + "levels";
	if (std::filesystem::exists(levelsDir))
	{
		for (const auto& entry : std::filesystem::directory_iterator(levelsDir))
		{
			if (entry.path().extension() != ".txt")
				continue;

			const std::string filename = entry.path().filename().string();
			const std::string label = entry.path().stem().string();

			if (ImGui::Button(label.c_str(), { 160.f, 0.f }))
				game.scenes().replace(std::make_unique<PlayScene>(game, "levels/" + filename));
		}
	}
	else
	{
		ImGui::Text("Aucun niveau trouve.");
	}

	ImGui::Separator();
	if (ImGui::Button("Retour", { 160.f, 0.f }))
		game.scenes().pop();

	ImGui::End();
}
