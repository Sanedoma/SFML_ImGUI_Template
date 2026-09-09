#include "Scenes/SettingsScene.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "ImGui/imgui.h"

#include "Core/Game.h"

void SettingsScene::handleEvent(const sf::Event& event)
{
	const auto* key = event.getIf<sf::Event::KeyPressed>();
	if (key && key->code == sf::Keyboard::Key::Escape)
		game.scenes().pop();
}

void SettingsScene::Render(sf::RenderWindow& window)
{
	sf::RectangleShape dim(sf::Vector2f(window.getSize()));
	dim.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(dim);

	const ImVec2 display = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos({ display.x * 0.5f, display.y * 0.5f }, ImGuiCond_Always, { 0.5f, 0.5f });
	ImGui::Begin("Options", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderFloat("Volume general", &masterVolume, 0.f, 100.f, "%.0f");
	ImGui::SliderFloat("Musique", &musicVolume, 0.f, 100.f, "%.0f");

	if (ImGui::Button("Retour", { 160.f, 0.f }))
		game.scenes().pop();

	ImGui::End();
}
