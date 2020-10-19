#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Animation.h"
using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(1024, 512), "SFML Tutorial", Style::Close /*| Style::Titlebar*/ | Style::Resize);

	RectangleShape player(Vector2f(117.0f, 108.0f));


	player.setPosition(Vector2f(100.0f, 230.0f));

	Texture playerTexture; 
	playerTexture.loadFromFile("player01Run.png"); 
	player.setTexture(&playerTexture); 


	Animation animation(&playerTexture, Vector2u(8, 1), 0.05f);

	float deltaTime = 0.0f;
	Clock clock;


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		animation.Update(0, deltaTime);
		player.setTextureRect(animation.uvRect);

		window.clear();
		window.draw(player);
		window.display();

		Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window.close();
				break;
			}

		}
	}
	return 0;
}
