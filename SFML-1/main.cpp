#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Animation.h"
#include "Player.h"
#include"Platform.h"
#include "bullet.h"


static const float VIEW_HIGHT = 720.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float (window.getSize().y);
    view.setSize(VIEW_HIGHT * aspectRatio, VIEW_HIGHT);
}
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1080, 720), "little red riding hood", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HIGHT, VIEW_HIGHT));
    sf::Texture playtexture;
    playtexture.loadFromFile("run_stay.png");
    

    Player player(&playtexture, sf::Vector2u(6, 2), 0.2f,150.0f,200.0f);

    sf::Texture BULLET;
    BULLET.loadFromFile("Gun.png");
    bullet bullet1(&BULLET, sf::Vector2u(4, 1), 0.2f, 150.0f,player.getPosition());

    std::vector<Platform>platforms;

    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(1080.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(150.0f, 400.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(900.0f, 400.0f)));


    float deltatime= 0.0f;
    sf::Clock clock;
    int b = 0;

    while (window.isOpen())
    {
        deltatime = clock.restart().asSeconds();
        if (deltatime > 1.0 / 20.0f)
            deltatime = 1.0 / 20.0f;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
			
			}
		}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
        {
            bullet1.attack(pos);
            b = 1;
        }
        if (b >= 1)
        {
            bullet1.update(deltaTime);
            bullet1.Draw(window);
            /*for (i = 0; i < 2; i++) {
                if (alienVector[i].hit() == 1)
                {
                    bullet1.del();
                }
            }*/
        }
        if (player.getPosition().x - bullet1.GetPosition().x <= -1000.0f)
        {
            b = 0;
            bullet1.isAvaliable();
        }
        player.Update(deltatime);
       
       
        sf::Vector2f direction;
        Collider playerCollision = player.GetCollider();
       
        for (Platform& platform : platforms)


            if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
                player.OnCollision(direction);
        
        

       
        view.setCenter(player.getPosition());

        window.clear();
        window.setView(view);
        player.Draw(window);
        for (Platform& platform : platforms)
        platform.Draw(window);
        window.display();
    }

    return 0;
}