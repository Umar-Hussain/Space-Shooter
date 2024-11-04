#pragma once
#ifndef  gameOver-H
#include"SFML/Graphics.hpp"
using namespace sf;
using namespace std;
class gameOver{
	Sprite  menuSprite;
	Texture menuTexture;
public:
	gameOver()
	{
		menuTexture.loadFromFile("assets/backgrounds/gameOver.jpg");
		menuSprite.setTexture(menuTexture);



	}
	void drawgameover(RenderWindow& window)

	{
		menuSprite.setScale(1200.0 / 1920, 900.0 / 1080);
		window.draw(menuSprite);


	}




};
#endif 

