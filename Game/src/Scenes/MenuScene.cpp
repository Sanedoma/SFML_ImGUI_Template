#include "Scenes/MenuScene.h"

#include <memory>

#include "ImGui/imgui.h"

#include "Core/Game.h"
#include "Scenes/PlayScene.h"

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

	if (ImGui::Button("Quitter", { 160.f, 0.f }))
		game.window().close();

	ImGui::End();
}
