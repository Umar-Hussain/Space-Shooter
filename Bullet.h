#pragma once
#ifndef BULLET.h
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include"SFML/Graphics/Texture.hpp"
#include"SFML/System.hpp"
#include<string>
#include<cstring>
#include"Player.h"
struct Coordinate {
	float x;
	float y;
};
class Bullet
{
private:
	float Speed;
	int Damage;
	bool isActive;
	Coordinate bulletCoordinates;
	Texture bulletTexture;
	Sprite bulletSprite;
public:
	Bullet()
	{
		isActive = false;
		bulletCoordinates.x = 100;
		bulletCoordinates.y = 100;
		Damage = 10;
	}
	void bulletInitializer(int damage = 12, float x = 200, float y = 300){
		Speed = 1.6f;
		bulletCoordinates.x = x;
		bulletCoordinates.y = y;
		bulletTexture.loadFromFile("assets/Bullets/LaserBlue01.png");
		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setPosition(x, y);
		isActive = true;
	}
	void moveBullet()
	{
		if (bulletCoordinates.y > 0)
			bulletCoordinates.y += Speed;
	
	}
	void drawBullet(RenderWindow& window)
	{
		if(isActive)
		window.draw(bulletSprite);
	}
	bool Active() const 
	{
		return isActive;
	}
	void update() {
		if (isActive) {
			bulletCoordinates.y -= Speed; 
			bulletSprite.setPosition(bulletCoordinates.x,bulletCoordinates.y);

			if (bulletCoordinates.y < 0) {
				isActive = false;
			}
		}
	}
	float getWidth() { return bulletSprite.getGlobalBounds().width; }
	float getHeight() { return bulletSprite.getGlobalBounds().height; }
	Coordinate getCoordinate()
	{
		return bulletCoordinates;
	}


};
#endif 