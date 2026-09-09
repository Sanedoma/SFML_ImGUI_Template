#include "ImGui/imgui.h"
#include "ImGui-SFML/imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "../Gameplay/Player.h"
#include "../Gameplay/Enemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Shoot'em Up");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    Player player;
    std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;

    // Quelques ennemis de test, répartis en haut de l'écran
    enemies.push_back(Enemy({ 100.f, 0.f }));
    enemies.push_back(Enemy({ 300.f, -100.f }));
    enemies.push_back(Enemy({ 500.f, -200.f }));
    enemies.push_back(Enemy({ 700.f, -50.f }));

    sf::Clock deltaClock;
	int score = 0;

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

        for (Enemy& enemy : enemies)
            enemy.Update(dt.asSeconds());

        // --- Collisions balle -> ennemi ---
        for (Bullet& bullet : bullets) {
            for (Enemy& enemy : enemies) {
                if (!bullet.isAlive() || !enemy.isAlive())
                    continue;

                if (bullet.getBounds().findIntersection(enemy.getBounds())) {
                    bullet.kill();
                    enemy.OnCollision(&bullet);
                    score += 100;
                }
            }
        }

		//--- Collisions joueur -> ennemi ---
		for (Enemy& enemy : enemies) {
			if (!enemy.isAlive())
				continue;
			if (player.getBounds().findIntersection(enemy.getBounds())) {
                player.TakeDammage(1);
				enemy.OnCollision(&player);

			}
		}


		//On supprime les balles et les enemies qui sont sorties de l'écran
		std::erase_if(bullets, [](const Bullet& b) { return b.isOffScreen() || !b.isAlive(); });
        std::erase_if(enemies, [](const Enemy& e) { return e.isOffScreen() || !e.isAlive(); });

        ImGui::Begin("Debug");
        ImGui::Text("Player Position: (%.0f, %.0f)", player.getPosition().x, player.getPosition().y);
		ImGui::Text("Bullets on screen: %d", (int)bullets.size());
        ImGui::Text(
			"space bar as been pressed %s",
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ? "true" : "false"
        );
        ImGui::Text("Enemies: %d", (int)enemies.size());
        ImGui::Text("Score: %d", score);
        ImGui::Text("Player HP: %d", player.getHealth());
        ImGui::End();


        // 3. RENDU
        window.clear(sf::Color::Black);   
        player.Render(window);
        for(Bullet& bullet : bullets)
			bullet.Render(window);
        for (Enemy& enemy : enemies)
            enemy.Render(window);
        ImGui::SFML::Render(window);      
        window.display();                 
    }

    ImGui::SFML::Shutdown();
}
