#pragma once

#ifndef ASTEROIDS_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include"SFML/Graphics/Texture.hpp"
#include"SFML/System.hpp"
#include<iostream>
#include "Bullet.h"

using namespace sf;

struct Coor {
    float x;
    float y;
};

class Asteroid {
    Texture asteroidTexture;
    Sprite asteroidSprite;
    float speed;
    Coor asteroidCoordinates;

    std::vector<Texture> explosionTextures;
    Sprite explosionSprite;
    Clock explosionClock;
    bool isExploding;
    int currentFrame;
    bool isFalling;

public:
    Asteroid(int x = 400, int y = 50)
        : speed(0.1f), isExploding(false), currentFrame(0)
    {
        
        asteroidTexture.loadFromFile("assets/small_GreyAsteroid.png");
        asteroidSprite.setTexture(asteroidTexture);
        asteroidCoordinates.x = x;
        asteroidCoordinates.y = y;

        for (int i = 0; i < 25; ++i) {
            Texture texture;
            std::string texturePath = (i < 10)
                ? "assets/Smoke/blackSmoke0" + std::to_string(i) + ".png"
                : "assets/Smoke/blackSmoke" + std::to_string(i) + ".png";
            texture.loadFromFile(texturePath);
            explosionTextures.push_back(texture);
        }
    }

    void fall(float deltaTime) {
        if (!isExploding) {
            asteroidCoordinates.y += speed;
            asteroidSprite.setPosition(asteroidCoordinates.x, asteroidCoordinates.y);
        }
    }

    Sprite getSprite() {
        asteroidTexture.loadFromFile("assets/small_GreyAsteroid.png");
        asteroidSprite.setTexture(asteroidTexture);
        asteroidSprite.setScale(1.2, 1.2);
        return asteroidSprite;
    }

    FloatRect getBounds() {
        return asteroidSprite.getGlobalBounds();
    }

    bool isOutOfBounds(int windowHeight) {
        return asteroidSprite.getPosition().y > windowHeight;
    }

    Coor getCoordinates() {
        return asteroidCoordinates;
    }

    bool checkBulletCollision(Bullet& bullet) {
        float asteroidWidth = asteroidSprite.getGlobalBounds().width;
        float asteroidHeight = asteroidSprite.getGlobalBounds().height;

        float bulletWidth = 10;
        float bulletHeight = 10;

        bool collisionX = bullet.getCoordinate().x < asteroidCoordinates.x + asteroidWidth &&
            bullet.getCoordinate().x + bulletWidth > asteroidCoordinates.x;

        bool collisionY = bullet.getCoordinate().y < asteroidCoordinates.y + asteroidHeight &&
            bullet.getCoordinate().y + bulletHeight > asteroidCoordinates.y;

        return collisionX && collisionY;
    }

    void explode(RenderWindow& window) {
        isExploding = true;
        explosionClock.restart();
        currentFrame = 0;
        explosionSprite.setPosition(asteroidCoordinates.x, asteroidCoordinates.y);
    }

    void animate(RenderWindow& window) {
        if (isExploding) {
            float elapsedTime = explosionClock.getElapsedTime().asSeconds();

            if (elapsedTime >= 0.08f) {
                currentFrame++;
                explosionClock.restart();
            }

            if (currentFrame < 20) {
                explosionSprite.setTexture(explosionTextures[currentFrame]);
                explosionSprite.setPosition(asteroidCoordinates.x, asteroidCoordinates.y);
                explosionSprite.setScale(.3, .3);
                window.draw(explosionSprite);
            }
            else {
                isExploding = false;  
            }
        }
    }

    bool isExplodingg() {
        return isExploding;
    }
    int getCurrentFrame()
    {
        return currentFrame;
    }
   

};

#endif
