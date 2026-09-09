#include "ImGui/imgui.h"
#include "ImGui-SFML/imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Shoot'em Up");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    Player player;

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        // 1. ENTRÉES
        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // 2. UPDATE
        const sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        player.Update(dt.asSeconds());

        ImGui::Begin("Debug");
        ImGui::Text("Player Position: (%.0f, %.0f)", player.getPosition().x, player.getPosition().y);
        ImGui::End();

        // 3. RENDU
        window.clear(sf::Color::Black);   
        player.Render(window);            
        ImGui::SFML::Render(window);      
        window.display();                 
    }

    ImGui::SFML::Shutdown();
}