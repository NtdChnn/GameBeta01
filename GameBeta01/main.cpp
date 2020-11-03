#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Animation.h"
using namespace sf;
using namespace std;

static const float VIEW_HIGHT = 1000.0f;
static const float VIEW_WIDTH = 700.0f;

void ResizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HIGHT * aspectRatio, VIEW_WIDTH);
}

int main()
{
	RenderWindow window(VideoMode(1000, 700), "SFML Tutorial", Style::Close | Style::Resize);

	RectangleShape player(Vector2f(117.0f, 108.0f));
	RectangleShape BG01(Vector2f(7260, 700));

	player.setPosition(Vector2f(500.0f, 470.0f));
	BG01.setPosition(Vector2f(0.0f, 120.0f));

	View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HIGHT,VIEW_WIDTH));
	player.setOrigin(300.0f, -105.0f);

	Texture playerTexture; 
	playerTexture.loadFromFile("player01Run.png"); 
	player.setTexture(&playerTexture); 

	Texture BG01Texture;
	BG01Texture.loadFromFile("BGForestNight.png");
	BG01.setTexture(&BG01Texture);

	Animation animationplayer(&playerTexture, Vector2u(8, 1), 0.05f);

	float deltaTime = 0.0f;
	Clock clock;
	int move = 0;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		player.setTextureRect(animationplayer.uvRect);

		if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			move = 1;
		}
		if (move == 1)
		{
			player.move(0.05f, 0.0f);
			animationplayer.Update(0, deltaTime);
			player.setTextureRect(animationplayer.uvRect);
		}

		window.clear();
		window.draw(BG01);
		view.setCenter (player.getPosition());
		window.setView(view);
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
			case Event::Resized:
				ResizeView(window, view);
			}

		}
	}
	return 0;
}
