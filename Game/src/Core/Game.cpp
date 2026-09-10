#include "Core/Game.h"

#include <memory>
#include <optional>

#include <SFML/Window/Event.hpp>

#include "ImGui-SFML/imgui-SFML.h"

#include "Core/Config.h"
#include "Scenes/MenuScene.h"

Game::Game()
	: renderWindow(sf::VideoMode({ cfg::WindowWidth, cfg::WindowHeight }), cfg::WindowTitle)
{
	renderWindow.setFramerateLimit(60);
	imguiReady = ImGui::SFML::Init(renderWindow);

	sceneManager.push(std::make_unique<MenuScene>(*this));
	sceneManager.applyPending();
}

Game::~Game()
{
	if (imguiReady)
		ImGui::SFML::Shutdown();
}

void Game::Run()
{
	while (renderWindow.isOpen())
	{
		processEvents();

		const sf::Time dt = clock.restart();
		if (imguiReady)
			ImGui::SFML::Update(renderWindow, dt);
		sceneManager.Update(dt.asSeconds());

		renderWindow.clear();
		sceneManager.Render(renderWindow);
		if (imguiReady)
			ImGui::SFML::Render(renderWindow);
		renderWindow.display();

		sceneManager.applyPending();
	}
}

void Game::processEvents()
{
	while (const std::optional<sf::Event> event = renderWindow.pollEvent())
	{
		if (imguiReady)
			ImGui::SFML::ProcessEvent(renderWindow, *event);

		if (event->is<sf::Event::Closed>())
			renderWindow.close();
		else
			sceneManager.handleEvent(*event);
	}
}
