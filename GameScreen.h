#pragma once
#ifndef GAMESCREEN.H

 // !GAMESCREEN.H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include"SFML/Graphics/Texture.hpp"
#include"SFML/System.hpp"
#include<string>
#include<cstring>
using namespace sf;
using namespace std;
class gameScreen {
	string state;
	Sprite backgroundSprite;
	Texture backgroundTexture;
public:
	gameScreen()
	{
		state = "start";
		backgroundTexture.loadFromFile("assets/backgrounds/background2.png");
		backgroundSprite.setTexture(backgroundTexture);
		//backgroundSprite.setScale(1200 / 1080.0, 900.0 / 1920);
	}
	string getState()
	{
		return state;
	}
	void setState(string s)
	{
		this->state = s;
	}
	void draw(RenderWindow& window)
	{
		window.draw(backgroundSprite);
	}



}; 
#endif