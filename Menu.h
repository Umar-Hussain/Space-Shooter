#pragma once
#ifndef  MENU-H
#include"SFML/Graphics.hpp"
using namespace sf;
using namespace std;
class Menu {
	Sprite  menuSprite;
	Texture menuTexture;
public:
	Menu()
	{
		menuTexture.loadFromFile("assets/Menu.png");
		menuSprite.setTexture(menuTexture);
	
	
	
	}
	void drawMenu(RenderWindow& window)
	
	{
		menuSprite.setScale(1200.0/1920, 900.0/1080);
		window.draw(menuSprite);
	
	
	}




};
#endif // ! MENU-H

