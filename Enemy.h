#pragma once
#ifndef  Enemy_H
#include"Bullet.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include"SFML/Graphics/Texture.hpp"
#include"SFML/System.hpp"
#include<iostream>
#include "Asteroids.h"

using namespace sf;



class Enemy {
private:
    Sprite enemySprite;
    Texture enemyTexture;
    vector<Sprite> bullets;
    Texture bulletTexture;
    float shootTimer; 
    float moveSpeed; 
    int Health;

public:
    Enemy() {
        Health = 200;
        enemyTexture.loadFromFile("assets/enemies/enemy2.png");
        enemySprite.setTexture(enemyTexture);
        enemySprite.setPosition(600, 100);
        enemySprite.setScale(250.0 / 437, 250.0 / 570);
        bulletTexture.loadFromFile("assets/Bullets/laserBlue01.png");
       
        shootTimer = 0;
        moveSpeed = 2.0f; 
    }
    Enemy(int x, int y) {
        std::cout << "Spawned enemy at X: " << x << std::endl;
    //    std::cout << "Number of enemies: " <<size << std::endl;

        Health =20;
        enemyTexture.loadFromFile("assets/enemies/ship6.png");
        enemySprite.setTexture(enemyTexture);
        enemySprite.setPosition(x, y);
        enemySprite.setScale(100.0 / 127, 100.0 / 127);
        bulletTexture.loadFromFile("assets/Bullets/bullet.png");

        shootTimer = 0;
        moveSpeed = 2.0f;
    }
    void move(float deltaTime) {
        static bool movingRight = true;
        static bool moveDown = true;
        
        if (movingRight) {
            enemySprite.move(moveSpeed * 0.05, 0);
            if (moveDown)
            {
                enemySprite.move(0,moveSpeed * 0.02);
                if (enemySprite.getPosition().y > 400)
                    moveDown = false;
            }

            else {
                enemySprite.move(0, -moveSpeed * 0.02);
                if (enemySprite.getPosition().y < 0)
                    moveDown = true;
            }

            if (enemySprite.getPosition().x >= 950)
                movingRight = false;
        }
        else {
            enemySprite.move(-moveSpeed * 0.05, 0);
            if (moveDown)
            {
                enemySprite.move(0, moveSpeed * 0.02);
                if (enemySprite.getPosition().y > 400)
                    moveDown = false;
            }

            else {
                enemySprite.move(0, -moveSpeed * 0.02);

                if (enemySprite.getPosition().y < 0)
                    moveDown = true;
            }
            if (enemySprite.getPosition().x <= 300)
                movingRight = true;
        }
    }

    void shoot(float deltaTime) {
        shootTimer += deltaTime;

        
        if (shootTimer >= 1.0f) {
            Sprite bullet(bulletTexture);
            bullet.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2, enemySprite.getPosition().y + enemySprite.getGlobalBounds().height);
            bullets.push_back(bullet);
            shootTimer = 0;
        }

   
        for (size_t i = 0; i < bullets.size(); ++i) {
            bullets[i].move(0, 300 * deltaTime); 
            if (bullets[i].getPosition().y > 900) {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }
    }

    void draw(RenderWindow& window,bool eq=false) {
        if (eq)
        {
            enemyTexture.loadFromFile("assets/enemies/ship6.png");
            enemySprite.setTexture(enemyTexture);
        }
            
        window.draw(enemySprite);
        for (auto& bullet : bullets) {
            window.draw(bullet);
        }
    }

    const FloatRect getBounds() const {
        return enemySprite.getGlobalBounds();
    }

    vector<Sprite>& getBullets() {
        return bullets;
    }
        void takeDamage(int d)
        {
            Health -= d;
         
        }
        FloatRect getGlobalBounds() {
            return enemySprite.getGlobalBounds();
        }
        int getHealth()
        {
            return Health;
        
        }
};

#endif // ! Enemy_H

