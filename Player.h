#pragma once
#ifndef PLAYER.H
const int maxBullets = 10;
 // !PLAYER.H
#include"Bullet.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include"SFML/Graphics/Texture.hpp"
#include"SFML/System.hpp"
#include<iostream>
#include "Asteroids.h"
const int globalBoundsX = 1200;
const int globalBoundsY = 900;
using namespace sf;
struct Coordinates {
	float x;
	float y;
};
class Player
{
protected:
	int Lives;
	int Damage;
	int Health;
	float Speed;
	Bullet bullet[maxBullets];
	Coordinates playerCoordinates;
	Sprite playerSprite;
	Texture playerTexture;
	int bulletCount;
	
public:
	Player()
	{
		bulletCount = 0;
		Lives = 3;
		Damage = 12;
		Health = 200;
		playerCoordinates.x = 600;
		playerCoordinates.y = 400;
		playerTexture.loadFromFile("assets/Player.png");
		playerSprite.setPosition(playerCoordinates.x, playerCoordinates.y);
		playerSprite.setTexture(playerTexture);
		playerSprite.setScale(.1, .1);
		Speed = 0.8f;
		
		
	}
	Player(bool e)
	{
		bulletCount = 0;
		Lives = 1;
		Damage = 12;
		Health = 200;
		playerCoordinates.x = 600;
		playerCoordinates.y = 100;
		playerTexture.loadFromFile("assets/enemies/enemy2.png");
		playerSprite.setPosition(playerCoordinates.x, playerCoordinates.y);
		playerSprite.setTexture(playerTexture);
		playerSprite.setScale(250.0/437, 250.0/570);
		Speed = 0.3f;
	}
	void drawPlayer(RenderWindow& window)
	{

		playerSprite.setPosition(playerCoordinates.x, playerCoordinates.y);
		window.draw(playerSprite);
		for (int i = 0; i < bulletCount; ++i) {
			bullet[i].drawBullet(window);
		}
	}
	void drawEnemy(RenderWindow& window)
	{
		playerSprite.setPosition(playerCoordinates.x, playerCoordinates.y);
		window.draw(playerSprite);
	}
  
	void moveLeft()
	{
		  if(playerCoordinates.x>10)
			playerCoordinates.x -= Speed;

	}
	Coordinates getCoordinates()
	{
		return playerCoordinates;
	
	}
	void moveRight()
	{       
		if (playerCoordinates.x < (globalBoundsX-70))
			playerCoordinates.x += Speed;
		/*cout << "Hello";*/
	}
	void moveUp()
	{
		if (playerCoordinates.y > 50)
			playerCoordinates.y -= Speed;
		//	cout << "hello y";

	}
	void moveDown()
	
	{
		if (playerCoordinates.y < (globalBoundsY - 100) && playerCoordinates.y>0)
		{
			//cout << "Move " << playerCoordinates.y << endl;
			playerCoordinates.y += Speed;
			
		}
	
	}
	void updateBullets() {
		for (int i = 0; i < bulletCount; ++i) {
			bullet[i].update();
			if (!bullet[i].Active()) {
				bullet[i] = bullet[bulletCount - 1]; 
				bulletCount--; 
				i--; 
			}
		}
	}
	void shoot() {
		if (bulletCount < maxBullets) { 
			bullet[bulletCount].bulletInitializer(Damage, playerCoordinates.x + playerSprite.getGlobalBounds().width / 2, playerCoordinates.y);
			bulletCount++;
		}
	}
	int getHealth()
	{
		return Health;
	}
	void handleMovements()
	{   if (Keyboard::isKeyPressed(Keyboard::W)) {
                moveUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                moveLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                moveDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                moveRight();
            }
			if(Keyboard::isKeyPressed(Keyboard::Space))
		
			shoot();
	
	}
	void takeDamage(int damage)
	{
		this->Health -= damage;
		if (Health <= 0)
			this->Lives--;
	}
	bool checkCollision(Coor asteroidCoordinates) {
		float playerWidth = playerSprite.getGlobalBounds().width;
		float playerHeight = playerSprite.getGlobalBounds().height;

		float asteroidWidth = 50;  
		float asteroidHeight = 50; 
		/*cout << "Player Y" << playerCoordinates.y << endl;
	*/
		bool collisionX = playerCoordinates.x < asteroidCoordinates.x + asteroidWidth &&
			playerCoordinates.x + playerWidth > asteroidCoordinates.x;

		bool collisionY = playerCoordinates.y < asteroidCoordinates.y + asteroidHeight &&
			playerCoordinates.y + playerHeight > asteroidCoordinates.y;

		return collisionX && collisionY;
	}
 int bulletsSize()
	{
	 return bulletCount;
	 
	}
 void decBullet()
 {
	 bulletCount--;
 }
 Bullet* getBullets() {
	 return bullet;
 }
 void updateLives()
 {
	 Lives -= 1;
 }
 int getLives()
 {
	 return Lives;
 
 }
 FloatRect getGlobalBounds() {
	 return playerSprite.getGlobalBounds();
 }
};

#endif
