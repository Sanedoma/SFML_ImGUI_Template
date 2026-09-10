#include "Scenes/GameOverScene.h"

#include <memory>

#include "ImGui/imgui.h"

#include "Core/Game.h"
#include "Scenes/MenuScene.h"
#include "Scenes/PlayScene.h"

void GameOverScene::Render(sf::RenderWindow& window)
{
	window.clear(sf::Color(24, 10, 12));

	const ImVec2 display = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos({ display.x * 0.5f, display.y * 0.5f }, ImGuiCond_Always, { 0.5f, 0.5f });
	ImGui::Begin("Game Over", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Game Over");
	ImGui::Text("Score : %d", finalScore);
	ImGui::Separator();

	if (ImGui::Button("Rejouer", { 160.f, 0.f }))
		game.scenes().replace(std::make_unique<PlayScene>(game));

	if (ImGui::Button("Menu principal", { 160.f, 0.f }))
		game.scenes().replace(std::make_unique<MenuScene>(game));

	ImGui::End();
}
