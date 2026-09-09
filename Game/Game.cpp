#include "ImGui/imgui.h"
#include "ImGui-SFML/imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Shoot'em Up");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    Player player;
    std::vector<Bullet> bullets;

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

        if (auto newBullet = player.TryShoot())
            bullets.push_back(*newBullet);

        for(Bullet& bullet : bullets)
			bullet.Update(dt.asSeconds());

		//On supprime les balles qui sont sorties de l'écran
		std::erase_if(bullets, [](const Bullet& b) { return b.isOffScreen(); });

        ImGui::Begin("Debug");
        ImGui::Text("Player Position: (%.0f, %.0f)", player.getPosition().x, player.getPosition().y);
		ImGui::Text("Bullets on screen: %d", (int)bullets.size());
        ImGui::Text(
			"space bar as been pressed %s",
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ? "true" : "false"
        );
        ImGui::End();


        // 3. RENDU
        window.clear(sf::Color::Black);   
        player.Render(window);
        for(Bullet& bullet : bullets)
			bullet.Render(window);
        ImGui::SFML::Render(window);      
        window.display();                 
    }

    ImGui::SFML::Shutdown();
}