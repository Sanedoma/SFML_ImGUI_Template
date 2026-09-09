#include "Scenes/VictoryScene.h"

#include <memory>

#include "ImGui/imgui.h"

#include "Core/Game.h"
#include "Scenes/MenuScene.h"
#include "Scenes/PlayScene.h"

void VictoryScene::Render(sf::RenderWindow& window)
{
	window.clear(sf::Color(12, 24, 16));

	const ImVec2 display = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos({ display.x * 0.5f, display.y * 0.5f }, ImGuiCond_Always, { 0.5f, 0.5f });
	ImGui::Begin("Victoire", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Victoire !");
	ImGui::Text("Score : %d", finalScore);
	ImGui::Separator();

	if (ImGui::Button("Rejouer", { 160.f, 0.f }))
		game.scenes().replace(std::make_unique<PlayScene>(game));

	if (ImGui::Button("Menu principal", { 160.f, 0.f }))
		game.scenes().replace(std::make_unique<MenuScene>(game));

	ImGui::End();
}
