#include "Scenes/PauseScene.h"

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "ImGui/imgui.h"

#include "Core/Game.h"
#include "Scenes/MenuScene.h"

void PauseScene::handleEvent(const sf::Event& event)
{
	const auto* key = event.getIf<sf::Event::KeyPressed>();
	if (key && key->code == sf::Keyboard::Key::Escape)
		game.scenes().pop();
}

void PauseScene::Render(sf::RenderWindow& window)
{
	sf::RectangleShape dim(sf::Vector2f(window.getSize()));
	dim.setFillColor(sf::Color(0, 0, 0, 150));
	window.draw(dim);

	const ImVec2 display = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos({ display.x * 0.5f, display.y * 0.5f }, ImGuiCond_Always, { 0.5f, 0.5f });
	ImGui::Begin("Pause", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Reprendre", { 160.f, 0.f }))
		game.scenes().pop();

	if (ImGui::Button("Menu principal", { 160.f, 0.f }))
	{
		game.scenes().clear();
		game.scenes().push(std::make_unique<MenuScene>(game));
	}

	if (ImGui::Button("Quitter", { 160.f, 0.f }))
		game.window().close();

	ImGui::End();
}
