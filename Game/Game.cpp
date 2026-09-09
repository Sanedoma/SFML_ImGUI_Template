#include "ImGui/imgui.h"
#include "ImGui-SFML/imgui-SFML.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Shoot'em Up");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	// --- Le joueur ---
	Player player;

	sf::Clock deltaClock;

	//Execution de la boucle principale (par frame)
	while (window.isOpen()){
		// Les entrées utilisateur
		while (const auto event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);
			if(event->is<sf::Event::Closed>()){
				window.close();
			}
		}

		// Phase d'update
		const sf::Time dt = deltaClock.restart();
		ImGui::SFML::Update(window, dt);
		// Logique de jeu (déplacement du joueur)
		player.Update(dt.asSeconds());
		player.Render(window);

		// Panneau de débug ImGui
		ImGui::Begin("Debug");
		ImGui::Text("Player Position: (%.0f, %.0f)", player.getPosition().x, player.getPosition().y);
		ImGui::End();

		// Phase de rendu
		window.clear(sf::Color::Black);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}