#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <sstream> 
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
	srand(time(NULL));

	RenderWindow window(VideoMode(1000, 700), "SFML Tutorial", Style::Close | Style::Resize);

	RectangleShape player(Vector2f(117.0f, 108.0f));
	//BG
	RectangleShape BG01(Vector2f(7260, 700));
	//enermy
	RectangleShape enermy01(Vector2f(.0f, .0f));
	//obstrution
	RectangleShape timber01(Vector2f(64.25f,31.75f));
	RectangleShape timber02(Vector2f(62.0f, 29.75f));
	RectangleShape rock01(Vector2f(98.5f, 37.0f));
	RectangleShape rock02(Vector2f(88.5f,28.0f));

	View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HIGHT, VIEW_WIDTH));
	player.setOrigin(300.0f, -105.0f);
	timber01.setOrigin(0.0f,31.75f);
	timber02.setOrigin(0.0f,29.75f);
	rock01.setOrigin(0.0f, 37.0f);
	rock02.setOrigin(0.0f, 28.0f);

	player.setPosition(Vector2f(500.0f, 350.0f));
	BG01.setPosition(Vector2f(0.0f, 0.0f));
	//timber01.setPosition(Vector2f(500.0f,510.25f));
	//timber02.setPosition(Vector2f(700.0f,510.25f));
	rock01.setPosition(Vector2f(1500.0f, 542.0f));
	rock02.setPosition(Vector2f(1000.0f, 542.0f));

	Texture playerTexture; 
	playerTexture.loadFromFile("player01Run.png"); 
	player.setTexture(&playerTexture);

	Texture BG01Texture;
	BG01Texture.loadFromFile("BGForestNight.png");
	BG01.setTexture(&BG01Texture);

	Texture timber01Texture;
	timber01Texture.loadFromFile("timber_01bgremove.png");
	timber01.setTexture(&timber01Texture);
	Texture timber02Texture;
	timber02Texture.loadFromFile("timber_02bgremove.png");
	timber02.setTexture(&timber02Texture);
	Texture rock01Texture;
	rock01Texture.loadFromFile("rock_01bgremove.png");
	rock01.setTexture(&rock01Texture);
	Texture rock02Texture;
	rock02Texture.loadFromFile("rock_02bgremove.png");
	rock02.setTexture(&rock02Texture);

	Font gameFont;
	if (!gameFont.loadFromFile("PixelEmulator-xq08.ttf")) {}

	//GameOver
	Color gameOverColor(255, 255, 255, 50);
	RectangleShape gameOverBG(Vector2f(1000, 700));
	gameOverBG.setFillColor(gameOverColor);

	Text gameOverText;
	gameOverText.setFont(gameFont);
	gameOverText.setFillColor(Color::Black);
	gameOverText.setStyle(Text::Regular);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(100);

	//Pause
	Color pauseColor(0, 0, 0, 70);
	RectangleShape pauseBG(Vector2f(1000, 700));
	pauseBG.setFillColor(pauseColor);

	Text pauseText01;
	pauseText01.setFont(gameFont);
	pauseText01.setFillColor(Color::White);
	pauseText01.setStyle(Text::Regular);
	pauseText01.setString("PAUSE");
	pauseText01.setCharacterSize(100);

	Text pauseText02;
	pauseText02.setFont(gameFont);
	pauseText02.setFillColor(Color::White);
	pauseText02.setStyle(Text::Regular);
	pauseText02.setString("Press 'P' to continue");
	pauseText02.setCharacterSize(50);

	//Score
	int currentScore = 0;

	RectangleShape scoreBG(Vector2f(7260.0f,40.0f));
	scoreBG.setFillColor(Color::Black);
	scoreBG.setPosition(Vector2f(0.0f, 90.0f));

	Text score;
	score.setFont(gameFont);
	score.setFillColor(Color::White);
	score.setStyle(Text::Regular);
	score.setString("Score");
	score.setCharacterSize(20);


	Text scoreCurrent;
	scoreCurrent.setFont(gameFont);
	scoreCurrent.setFillColor(Color::White);
	scoreCurrent.setStyle(Text::Regular);
	scoreCurrent.setCharacterSize(20);

	Animation animationplayer(&playerTexture, Vector2u(8, 1), 0.05f);

	float deltaTime = 0.0f;
	Clock clock;
	int move = 0, jump = 0 , gameOver = 0, pause = 0;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		player.setTextureRect(animationplayer.uvRect);

		if (Keyboard::isKeyPressed(Keyboard::Key::A) && jump == 0 && gameOver == 0 && pause == 0)
		{	
			move = 1;	
			jump = 1;	
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::P) && gameOver == 0)
		{
			if (pause == 0)
			{
				pause = 1;
			}
			else pause = 0; Sleep(200);
		}
		if (move == 1 && pause == 0)
		{
			player.move(0.4f, 0.0f);
			animationplayer.Update(0, deltaTime);
			player.setTextureRect(animationplayer.uvRect);
			currentScore += 1;
		}
		if (jump == 1 && pause == 0)
		{ player.move(0.0f, -0.4f); }
		int yplayer = player.getPosition().y;
		int xplayer = player.getPosition().x;
		if (yplayer == 150 && pause == 0)
		{ jump = 2; }
		if (jump == 2 && player.getPosition().y < 350 && pause == 0)
		{ player.move(0.0f, 0.4f); }
		if (yplayer == 350 && pause == 0)
		{ jump = 0 ; }

		printf("player x y = %d %d \t jump status = %d \n",xplayer,yplayer,jump);

		if (rock01.getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			move = 0; gameOver = 1;
		}
		if (rock02.getGlobalBounds().intersects(player.getGlobalBounds()))
		{
			move = 0; gameOver = 1;
		}

		score.setPosition(player.getPosition().x + 200, 100);
		scoreCurrent.setPosition(player.getPosition().x + 300, 100);
		gameOverBG.setPosition(player.getPosition().x - 500, 0);
		gameOverText.setPosition(player.getPosition().x - 325, 200);
		pauseBG.setPosition(player.getPosition().x - 500, 0);
		pauseText01.setPosition(player.getPosition().x - 325, 200);
		pauseText02.setPosition(player.getPosition().x - 325, 300);
		stringstream scoreShow;
		scoreShow << currentScore;
		scoreCurrent.setString(scoreShow.str().c_str());

		window.clear();
		window.draw(BG01);
		//window.draw(timber01);
		//window.draw(timber02);
		window.draw(scoreBG);
		window.draw(score);
		window.draw(scoreCurrent);
		window.draw(rock01);
		window.draw(rock02);
		view.setCenter (player.getPosition().x, 350.0f);
		window.setView(view);
		window.draw(player);
		if (gameOver == 1)
		{
			window.draw(gameOverBG);
			window.draw(gameOverText);
		}
		if (pause == 1)
		{
			window.draw(pauseBG);
			window.draw(pauseText01);
			window.draw(pauseText02);
			Sleep(200);
		}
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